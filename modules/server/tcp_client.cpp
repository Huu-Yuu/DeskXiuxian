#include "tcp_client.h"

TcpClient::TcpClient(QObject* parent) : QObject(parent)
{
    if (tcp_socket_ == nullptr)
    {
        tcp_socket_ = new QTcpSocket();
        qRegisterMetaType<QAbstractSocket::SocketError>
        ("QAbstractSocket::SocketError");
        connect(tcp_socket_, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(SlotSocketErrorDeal(QAbstractSocket::SocketError)),
                Qt::QueuedConnection);
        connect(tcp_socket_, &QTcpSocket::readyRead, this, &TcpClient::SlotTcpRead, Qt::QueuedConnection);
        connect(tcp_socket_, &QTcpSocket::connected, this, &TcpClient::SlotConnected, Qt::QueuedConnection);
        connect(tcp_socket_, &QTcpSocket::disconnected, this, &TcpClient::SlotDisconnected, Qt::QueuedConnection);
    }
    if (reconnect_timer_ == nullptr)
    {
        reconnect_timer_ = new QTimer;
        connect(reconnect_timer_, &QTimer::timeout, this, &TcpClient::SlotReconnectTimeout, Qt::QueuedConnection);
    }
    user_ip_ = PublicFunc::GetLocalIpAddress();
    SlotTcpConnect();
}

TcpClient::~TcpClient()
{
    if (tcp_socket_ != nullptr)
    {
        //先断开，最后再释放
        tcp_socket_->disconnectFromHost();
        delete tcp_socket_;
        tcp_socket_ = nullptr;
    }
}

void TcpClient::SlotTcpConnect()
{
    tcp_socket_->abort();
    tcp_socket_->connectToHost(MAIN_SERVER_IP, MAIN_SERVER_PORT);
    reconnect_timer_->start(kTcpReconnectTimeoutVal_);
    qDebug() << "执行端口重连操作完成";
}

bool TcpClient::IsConnected()
{
    return connect_ok_;
}

void TcpClient::SlotConnected()
{
    connect_ok_ = true;
    qDebug() << "网络已连接，开始请求访问服务器";
    QJsonObject json_obj; //发送客户端信息
    json_obj.insert("SENDER", kClientName_);
    json_obj.insert("RECEIVER", kServerName_);
    json_obj.insert("TYPE", QString("%1").arg(kTcpRequestConnect));
    json_obj.insert("STATUS", "00");
    json_obj.insert("USERUUID", user_uuid_);
    json_obj.insert("USERIP", user_ip_);
    json_obj.insert("CURRENTTIME", GenerateTimeStamp());
    TcpWrite(json_obj);
}

qint64 TcpClient::TcpWrite(QJsonObject& json_data)
{
    QMutexLocker lock(&send_data_mutex_);
    // 打印发送的数据
    qDebug() << "Robot Json:" << json_data;
    if (connect_ctrl_ == "00")
    {
        int type = json_data.value("TYPE").toString().toInt();
        if (connect_ok_ || (type == 1)) // 判断是否连接成功或第一次连接
        {
            QJsonDocument json_doc(json_data);
            QByteArray json_byte_array = json_doc.toJson(QJsonDocument::Compact);
            qint64 result = tcp_socket_->write(json_byte_array);
            if (result != json_byte_array.length())
            {
                if (type < 300)
                {
                    qDebug() <<
                             QString("socket 数据发送不完整。待发送数据长度： %1, 已发送数据长度： %1。")
                             .arg(json_byte_array.length()).arg(result);
                }
            }
            return result;
        }
    }
    else
    {
        if (qsocket_error_fliter_ != ERROR_NETWORK_COMMU_REFUSE)
        {
            qsocket_error_fliter_ = ERROR_NETWORK_COMMU_REFUSE;
            qDebug() << QString("TcpWrite -> connect_ctrl_(%1) != 0.")
                     .arg(connect_ctrl_);
            reconnect_timer_->stop();
        }
        //拒绝连接还是输出计划发送的数据
        int type = json_data.value("TYPE").toString().toInt();
        if (type != 2)
        {
            //tr:机器人端网络数据：
            qDebug() << "Robot Json:" << json_data;
        }
    }
    return NO_ERROR;
}

QString TcpClient::GenerateTimeStamp()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}

void TcpClient::JsonDataDeal(const QByteArray& json_data)
{
    //收到调度服务器的回复
    //int result = NO_ERROR;
    QJsonParseError json_error;
    QJsonDocument json_analyse = QJsonDocument::fromJson(json_data, &json_error);
    bool select1 = (json_error.error == QJsonParseError::NoError);
    bool select2 = !(json_analyse.isEmpty() || json_analyse.isNull());
    bool select3 = json_analyse.isObject();
    if (select1 && select2 && select3)
    {
        QJsonObject obj = json_analyse.object();//取得最外层大对象
        //解析json
        TcpCmadType type = TcpCmadType(obj.value("TYPE").toString().toInt());
        if (type != 2)
        {
            // 打印发送的数据
            qDebug() << "Robot Json:" << json_data;
        }
        select1 = obj.contains("SENDER") && obj.contains("RECEIVER");
        select2 = obj.value("SENDER").toString() == kServerName_;
        select3 = obj.value("RECEIVER").toString() == kClientName_;
        if (select1 && select2 && select3)
        {
            TcpStatusType status = TcpStatusType(obj.value("STATUS")
                                                 .toString().toInt());
            //type检测, 语句后带break是要发送回复的，带return是已经有回复可以返回的
            if (connect_ctrl_ != "00")
            {
                if (qsocket_error_fliter_ != ERROR_NETWORK_COMMU_REFUSE)
                {
                    qsocket_error_fliter_ = ERROR_NETWORK_COMMU_REFUSE;
                    qDebug() << "通信标志为被标记为拒绝";
                    reconnect_timer_->stop();
                    return;
                }
            }
            else
            {
                switch (type)
                {
                    case kTcpRequestConnect:   //与服务器建立通信回复
                    {
                        connect_ctrl_ = obj.value("STATUS").toString();
                        if (status == kNegative)
                        {
                            qDebug() << (QString("服务器拒绝通信：(TYPE == %1 && STATUS == %2)").arg(type).arg(status));
                            emit SignalTcpErrorResult(ERROR_NETWORK_COMMU_REFUSE);
                            //主机指令状态不为0且处于非获取状态指令，不做动作直接返回。
                            return;
                        }
                        else if (status == kUnknow)
                        {
                            qDebug() << QString("TCP未知错误。(TYPE == %1 && STATUS == %2)")
                                     .arg(type).arg(status);
                            emit SignalTcpErrorResult(ERROR_NETWORK_UNKNOW_CMAD);
                            return;
                        }
                        connect_ok_ = true;
                        qDebug() << QString("与服务器建立通信确认，type == %1。").arg(type);
                        heart_beat_count_ = 0;

                        //此处增加服务器连接超时解除
                        QJsonObject extra;
                        extra.insert("faultReason", 2);
                        return;
                    }

                    case kTcpHeartBeats:   //获取修仙状态（心跳包）
                    {
                        ++heart_beat_count_;
                        if (connect_ok_)
                        {
                            qDebug() << "收到心跳包，重置网络重连定时器．";
                            reconnect_timer_->stop();
                            reconnect_timer_->start(kTcpReconnectTimeoutVal_);
                        }
                        break;
                    }
                    default:   //无效指令
                    {
                        obj.insert("STATUS", "01");
                        int error_code = ERROR_NETWORK_UNKNOW_CMAD;
                        obj.insert("errorCode", Logger::GetErrorCodeString(error_code));
                        obj.insert("errorInfo", Logger::GetErrorInfo(error_code));
                        qDebug() << QString("TCP无效指令，type == %1。").arg(type);
                        break; //发回去报错
                    }
                }
            }
            obj.insert("SENDER", kClientName_);
            obj.insert("RECEIVER", kServerName_);
            obj.insert("CURRENTTIME", GenerateTimeStamp());
            TcpWrite(obj);
        }
        else
        {
            qDebug() << QString("网络错误，头不匹配 json :" +
                                QString(json_analyse.toJson(QJsonDocument::Compact)));
            //emit SignalTcpResult(ERROR_NETWORK_HEAD_NOT_MATCH);
            return;
        }
    }
    else
    {
        qDebug() << ("网络头找不到! Server json data:" + json_data);
        //emit SignalTcpResult(ERROR_NETWORK_HEAD_NOT_VAILD);
        return;
    }
}

void TcpClient::SlotTcpRead()
{
    QByteArray data_buff = tcp_socket_->readAll();

    qDebug() << "读取到的内容 json data:" << data_buff;

    if (data_buff.isEmpty())
    {
        qDebug() << "没有SCOKET数据，返回";
        return;
    }

    if (data_buff.endsWith("\"}") || data_buff.endsWith("}}"))
    {
        //后者有尾，可能有头，可能无头
        if (data_keeper_.isEmpty())
        {
            if (!data_buff.startsWith("{\""))
            {
                //前者为空，后者有尾无头，直接丢弃
                return;
            }
        }
        if (!data_buff.startsWith("{\""))
        {
            //前者为头，后者为尾，拼接清空，继续处理
            data_keeper_ += data_buff;
            data_buff = JsonDataCheck(data_keeper_);
            if (!data_buff.isEmpty())
            {
                data_buff = data_keeper_;
                data_keeper_.clear();
            }
            else
            {
                qDebug() << QString("等待拼接数据大小：%1。").arg(data_keeper_.size());
                qDebug() << "等待拼接数据：" + data_keeper_;
                return;
            }
        }
        else
        {
            data_keeper_ += data_buff;
            data_buff = JsonDataCheck(data_keeper_);
            if (!data_buff.isEmpty())
            {
                data_buff = data_keeper_;
                data_keeper_.clear();
            }
            else
            {
                qDebug() << QString("等待拼接数据大小：%1。").arg(data_keeper_.size());
                qDebug() << "等待拼接数据：" + data_keeper_;
                return;
            }
        }
    }
    else if (data_buff.startsWith("{\""))
    {
        //后者有头无尾
        if (data_keeper_.isEmpty())
        {
            //前者为空，后者取代前者，带头。
            data_keeper_ = data_buff;
            return;
        }
        else
        {
            data_keeper_ += data_buff;
            data_buff = JsonDataCheck(data_keeper_);
            if (!data_buff.isEmpty())
            {
                data_buff = data_keeper_;
                data_keeper_.clear();
            }
            else
            {
                qDebug() << QString("等待拼接数据大小：%1。").arg(data_keeper_.size());
                qDebug() << "等待拼接数据：" + data_keeper_;
                return;
            }
        }
    }
    else
    {
        //无头无尾,直接拼接
        data_keeper_ += data_buff;
        return;
    }

    QList<QByteArray> json_list = DividePackage(data_buff);
    for (int i = 0; i < json_list.size(); ++i)
    {
        JsonDataDeal(json_list.at(i));
    }
}

QByteArray TcpClient::JsonDataCheck(QByteArray data)
{
    QByteArray check_data;
    QList<QByteArray> json_list = DividePackage(data);
    for (int i = 0; i < json_list.size(); ++i)
    {
        QJsonParseError json_error;
        QJsonDocument json_analyse = QJsonDocument::fromJson(json_list.at(i), &json_error);
        bool select1 = (json_error.error == QJsonParseError::NoError);
        bool select2 = (json_analyse.isEmpty() || json_analyse.isNull());
        bool select3 = json_analyse.isObject();
        if (!select1 || select2 || !select3)
        {
            json_list.removeAt(i);
            continue;
            //return false;
        }
    }

    for (int i = 0; i < json_list.size(); ++i)
    {
        check_data += json_list.at(i);
    }

    return check_data;
}

QList<QByteArray> TcpClient::DividePackage(QByteArray& package_data)
{
    int index = package_data.indexOf("}{");
    QByteArray sub_data;
    QList<QByteArray> data_list;
    while (index != -1)
    {
        sub_data.clear();
        sub_data = package_data.mid(0, index + 1);
        package_data.remove(0, index + 1);
        data_list.append(sub_data);
        index = package_data.indexOf("}{");
    }
    if (!package_data.isEmpty())
    {
        data_list.append(package_data);
    }
    return data_list;
}

void TcpClient::SlotDisconnected()
{
    qDebug() << "收到TCP网络连接已断开信号。";
    // 发送消息到界面

}

void TcpClient::SlotSocketErrorDeal(QAbstractSocket::SocketError socket_error)
{
    int error_num = socket_error;
    if (error_num == -1)
    {
        error_num = 0x99;
    }
    else if (error_num == 0)
    {
        error_num = 0x17;
    }
    int result = ERROR_QSOCKET_BASE | error_num;
    if (qsocket_error_fliter_ != result)
    {
        qsocket_error_fliter_ = result;
        emit SignalTcpErrorResult(result);
    }
}

void TcpClient::SlotReconnectTimeout()
{
    connect_ok_ = false;
    SlotTcpConnect();
    return;
}
