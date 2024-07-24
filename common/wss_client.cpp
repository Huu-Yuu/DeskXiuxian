#include "wss_client.h"
#include <QJsonDocument>

WssClient::WssClient(QString log_name, QString url, std::function<void (const QByteArray& obj)> func, bool ping,
                     ST_SSL_TYPE ssl_type, QStringList param)
{
    log_name_ = log_name;
    url_ = url;
    func_ = func;
    ping_ = ping;
    ssl_type_ = ssl_type;
    ssl_cert_addr_ = param;
    moveToThread(&thread_);
    thread_.start();
    connect(this, &WssClient::signalStart, this, &WssClient::slotStart);
    connect(this, &WssClient::signalSend, this, &WssClient::slotSend);
    connect(this, &WssClient::signalPing, this, &WssClient::slotPing);

    if(ping)
    {
        my_thread_.CreateThreadNew(&WssClient::PthreadSelf, this, NULL);
    }
}

WssClient::~WssClient()
{
    my_thread_.DestoryThreadNew();
    if(wss_client_)
    {
        delete  wss_client_;
        wss_client_ = nullptr;
    }
}

void WssClient::PthreadSelf(void* msg)
{
    QString url = url_;
    qDebug() << QString("%1 线程开始").arg(url);
    long long last_time = 0;
    while(!my_thread_.ThreadIsDestory())
    {
        if(GetConnected())
        {
            long long cur_t = QDateTime::currentMSecsSinceEpoch();

            if(cur_t < last_time)
            {
                last_time = cur_t;
            }
            if(cur_t - last_time > 3000)
            {
                emit signalPing();
            }
            last_time = cur_t;
        }
        usleep(100000);
    }

    my_thread_.ThreadDestoryFinish();
    qDebug() << QString("%1 线程结束").arg(url);
}

void WssClient::Init()
{
    emit signalStart();
}

void WssClient::slotStart()
{

    wss_client_ = new WebsocketClient(url_, ssl_type_, ssl_cert_addr_);
    wss_client_->SetReconnectTime(99999999);
    connect(wss_client_, &WebsocketClient::signalBinaryFrameReceived, this, &WssClient::slotMessageReceive);
//    connect(websocketClient_, &WebsocketClient::signalTextFrameReceived/*textMessageReceived*/,
//            this, &MovementWebsocketChannel1::SlotTextMessageReceive, Qt::UniqueConnection);
    connect(wss_client_, &WebsocketClient::signalConnected,
            this, [ = ]()
    {
        qDebug() << QString("%1 连接成功").arg(url_);
        SetConnected(true);
        signalConnectedStatus(1);
    });
    connect(wss_client_, &WebsocketClient::signalDisconnected,
            this, [ = ]()
    {
        qDebug() << QString("%1 连接断开").arg(url_);
        SetConnected(false);
        signalConnectedStatus(0);
    });
}

void WssClient::slotPing()
{
    wss_client_->Ping(QByteArray("GHI"));
}

void WssClient::slotMessageReceive(const QByteArray& frame, bool isLastFrame)
{
    static QByteArray frames;
    frames.append(frame);
    if(isLastFrame)
    {
        RecvData(frames);
        frames.clear();
    }
}

void WssClient::RecvData(const QByteArray& data)
{
    qDebug() << QString("recv:%1").arg(data.data());
    func_(data);
}


bool WssClient::Send(QByteArray qs)
{
    emit signalSend(qs);
    return true;
}

bool WssClient::slotSend(QByteArray qs)
{
    if(wss_client_)
    {
        wss_client_->onBinarySend(qs);
        qDebug() << QString("send:%1").arg(qs.data());
    }
    else
    {
        return false;
    }

    return true;
}

void WssClient::SetConnected(bool con)
{
    QMutexLocker lock(&is_connected_mutex_);
    is_connected_ = con;
}
bool WssClient::GetConnected()
{
    bool ret = false;
    QMutexLocker lock(&is_connected_mutex_);
    ret = is_connected_;

    return ret;
}
