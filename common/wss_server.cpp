#include "wss_server.h"
#include "my_std_thread.h"
#include <QJsonDocument>

WssServer::WssServer(QString log_name, int port, std::function<void (QObject* client, const QString& obj)> func, ST_SSL_TYPE ssl_type)
{
    log_name_ = log_name;
    port_ = port;
    func_ = func;
    ssl_type_ = ssl_type;
    moveToThread(&thread_);
    thread_.start();
    connect(this, &WssServer::signalStart, this, &WssServer::slotStart);
    connect(this, &WssServer::signalSend, this, &WssServer::slotSend);
}

WssServer::~WssServer()
{
    if(wss_server_)
    {
        delete  wss_server_;
        wss_server_ = nullptr;
    }
}

void WssServer::setTextSend(bool textsend)
{
    text_send_ = textsend;
}


void WssServer::Init()
{
    emit signalStart();
}

void WssServer::slotStart()
{
    qDebug() << QString("%1 wss server create").arg(port_);
    wss_server_ = new WebsocketServer(log_name_, ssl_type_);
    wss_server_->setTextSend(text_send_);
    connect(wss_server_, &WebsocketServer::signalListened, this, [&]()
    {
        qDebug() << QString("%1 监听完成").arg(port_);
    });
    WebSocketServer_Listen_Param param;
    param.port = port_;
    connect(wss_server_, &WebsocketServer::signalTextData, this,  &WssServer::RecvData);
    connect(wss_server_, &WebsocketServer::signalBinaryData, this,  &WssServer::RecvDataByte);
    wss_server_->startListen(param);

    connect(wss_server_, &WebsocketServer::signlNewConnectedObj, this, [&](QObject * client)
    {
        qDebug() << QString("有客户端连接上了");
        QMutexLocker lock(&clients_mutex_);
        clients_.push_back(client);
    });
    connect(wss_server_, &WebsocketServer::signlNewNoConnectedObj, this, [&](QObject * client)
    {
        qDebug() << QString("有客户端断开了");
        QMutexLocker lock(&clients_mutex_);
        for(auto iter = clients_.begin(); iter != clients_.end();)
        {
            if(*iter == client)
            {
                iter = clients_.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    });
}


void WssServer::RecvData(QObject* client, const QString& data)
{
    //LOG_INFO(log_name_.toStdString(), "recv:%p->%s", client, data.toStdString().c_str());
    func_(client, data);
}

void WssServer::RecvDataByte(QObject* client, const QByteArray& data)
{
    QString qs = data;
    func_(client, qs);
}




bool WssServer::Send(QObject* client, QString qs)
{
    emit signalSend(client, qs);
    return true;
}

bool WssServer::slotSend(QObject* client, QString qs)
{
    if(wss_server_)
    {
        wss_server_->slotTextSend(client, qs);
        //LOG_INFO(log_name_.toStdString(), "send:%p->%s", client, qs.toStdString().c_str());
    }
    else
    {
        return false;
    }

    return true;
}

int WssServer::ClientNum()
{
    int ret = 0;
    QMutexLocker lock(&clients_mutex_);
    for(auto iter = clients_.begin(); iter != clients_.end(); iter++)
    {
        ret++;
    }
    return ret;
}

QVector<QObject*> WssServer::GetClientList()
{
    QMutexLocker lock(&clients_mutex_);
    return clients_;
}
