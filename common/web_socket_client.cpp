#include "web_socket_client.h"
#include <QDebug>
#include <QEventLoop>
#include <QFile>
#include <QSslKey>

WebsocketClient::WebsocketClient(const QString& address,  ST_SSL_TYPE ssl_type, QStringList param)
{
    m_url_ = QUrl(address);
    DebugOutput(m_url_.toString());


    m_webSocket_ = new QWebSocket();
    switch(ssl_type)
    {
        case ST_SSL_TYPE::kSSL_NONE:
        {
            QSslConfiguration conf = m_webSocket_->sslConfiguration();
            conf.setPeerVerifyMode(QSslSocket::VerifyNone);
            conf.setProtocol(QSsl::TlsV1SslV3);
            m_webSocket_->setSslConfiguration(conf);
        }
        break;
        case ST_SSL_TYPE::kSSL_Cert_SINGLE:
        {
            //认证,只验证SSL服务端身份
            QSslConfiguration conf = m_webSocket_->sslConfiguration();
            QList<QSslCertificate> certlist = QSslCertificate::fromPath(":/localhost.cert");
            conf.setCaCertificates(certlist);
            QSslError error(QSslError::SelfSignedCertificate, certlist.at(0));
            QList<QSslError> expectedErrors;
            expectedErrors.append(error);
            m_webSocket_->ignoreSslErrors(expectedErrors);
            conf.setProtocol(QSsl::TlsV1SslV3);
            m_webSocket_->setSslConfiguration(conf);
        }
        break;
        case ST_SSL_TYPE::kSSL_Cert_Peer:
        {
            if(param.size() < 3)
            {
                qDebug() << "密钥文件路径不全" << param;
                break;
            }
            QSslConfiguration conf = m_webSocket_->sslConfiguration();
            // 创建客户端证书
            QFile t_file(SSL_FILE_SYSTE_PATH + param.at(1));
            t_file.open(QIODevice::ReadOnly);
            const QSslCertificate certificate(&t_file, QSsl::Pem);
            t_file.close();

            // 创建客户端私钥
            t_file.setFileName(SSL_FILE_SYSTE_PATH + param.at(2));
            t_file.open(QIODevice::ReadOnly);
            const QSslKey prvateKey(&t_file, QSsl::Rsa);
            t_file.close();

            // SSL验证模式；TLS协议版本
            conf.setProtocol(QSsl::TlsV1SslV3);
            conf.setPeerVerifyMode(QSslSocket::VerifyNone);
//            conf.setPeerVerifyDepth(1);
            conf.setLocalCertificate(certificate);
            conf.setPrivateKey(prvateKey);

            // 创建服务器端证书
            QList<QSslCertificate> caCerList;
            t_file.setFileName(SSL_FILE_SYSTE_PATH + param.at(0));
            t_file.open(QIODevice::ReadOnly);
            const QSslCertificate cACertificate(&t_file);
            // 将服务证书加入到CA列表中
            caCerList.append(cACertificate);
            conf.setCaCertificates(caCerList);
            t_file.close();
            m_webSocket_->setSslConfiguration(conf);
        }
        break;
        default:
            break;
    }

    connect(m_webSocket_, &QWebSocket::connected, this, &WebsocketClient::onConnected);
    connect(m_webSocket_, &QWebSocket::ping, this, &WebsocketClient::onPing);
    connect(m_webSocket_, &QWebSocket::pong, this, &WebsocketClient::onPong);
    connect(m_webSocket_, &QWebSocket::ping, this, [ = ](const QByteArray & payload)
    {
        emit m_webSocket_->pong(50, payload);
    });
    connect(m_webSocket_, &QWebSocket::disconnected, this, &WebsocketClient::onDisconnected);
    connect(m_webSocket_, &QWebSocket::connected, this, &WebsocketClient::signalConnected);
    connect(m_webSocket_, &QWebSocket::disconnected, this, &WebsocketClient::signalDisconnected);
    connect(m_webSocket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    m_webSocket_->open(m_url_);

    connect(&timer_, &QTimer::timeout, this, [ = ]()
    {
        DebugOutput(QString("reconnect... ") + m_url_.toString());
        emit signalDisconnected();
        if(m_webSocket_->isValid())
        {
            m_webSocket_->close();
        }
        m_webSocket_->open(m_url_);
    });
    timer_.start(timer_timeout_);

    QString text = "\n\n---------------------------------------------------------"
                   "-----------------------------------------------------------------";
    DebugOutput(text);
}

WebsocketClient::~WebsocketClient()
{
    m_webSocket_->abort();
    m_webSocket_->close();
    if(timer_.isActive())
        timer_.stop();
}

void WebsocketClient::SetReconnectTime(int timeout)
{
    if(timeout > 20000)
    {
        reconnect_time_without_data_ = timeout;
    }
    return;
}

void WebsocketClient::DebugOutput(const QString& content, int level)
{
    qDebug() << content;
    if (level > 1)
    {
        return ;
    }

    QString current_date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString log_dir_path = "../log/";//FileManager::GetLogDirPath();
    QString log_file_path = log_dir_path + current_date + "_websocket_server_log.txt";
    QString msg = "websocket 客户端：" + content;
}

qint64 WebsocketClient::onTextSend(const QString& data)
{
    if(m_webSocket_->isValid())
    {
        DebugOutput(QString(data), 2);
        return m_webSocket_->sendTextMessage(data);
    }
    return 0;
}

void WebsocketClient::Ping(QByteArray data)
{
    if(m_webSocket_ != nullptr && m_webSocket_->isValid())
    {
        m_webSocket_->ping(data);
    }
}

qint64 WebsocketClient::onBinarySend(const QByteArray& data)
{
    //qDebug()<<"onDataSend thread id:"<<QThread::currentThreadId();
    if(m_webSocket_->isValid())
    {
        DebugOutput(QString(data), 2);
        return m_webSocket_->sendBinaryMessage(data);
    }
    return 0;
}

void WebsocketClient::onConnected()
{
    if(timer_.isActive())
    {
        timer_.stop();
    }
    DebugOutput("connected " + m_url_.toString());
    timer_.start(reconnect_time_without_data_);

    connect(m_webSocket_, &QWebSocket::textFrameReceived,
            this, &WebsocketClient::signalTextFrameReceived, Qt::UniqueConnection);
    connect(m_webSocket_, &QWebSocket::binaryFrameReceived,
            this, &WebsocketClient::onBinaryFrameReceived, Qt::UniqueConnection);
}

void WebsocketClient::onBinaryFrameReceived(const QByteArray& frame, bool isLastFrame)
{
    timer_.start(reconnect_time_without_data_);
    emit signalBinaryFrameReceived(frame, isLastFrame);
}

void WebsocketClient::OnTextFrameReceived(const QString& frame, bool isLastFrame)
{
    timer_.start(reconnect_time_without_data_);
    emit signalTextFrameReceived(frame, isLastFrame);
}

void WebsocketClient::onPing(const QByteArray& content)
{
//    qDebug() << "websocket client ping " << content;
}

void WebsocketClient::onPong(quint64 elapsedTime, const QByteArray& payload)
{
//    qDebug() << "websocket client ping " << payload;
    Q_UNUSED(elapsedTime)
    Q_UNUSED(payload)
    //pong
    timer_.start(reconnect_time_without_data_);
}

void WebsocketClient::onError(QAbstractSocket::SocketError err)
{
    qDebug() << "websocket error:" << m_url_.toString() << err;
    DebugOutput("websocket error " + m_url_.toString() + QString::number(err) + ",desc:" + m_webSocket_->errorString());
}

void WebsocketClient::onDisconnected()
{
//    if(!timer_.isActive())
//    {
        timer_.start(timer_timeout_);
//    }
    DebugOutput("disconnected " + m_url_.toString());
}
