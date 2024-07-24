#include "web_socket_server.h"
#include <QWebSocket>


WebsocketServer::WebsocketServer(const QString& serverName, ST_SSL_TYPE ssl_type, QStringList param)
{
    Q_UNUSED(ssl_type);
    Q_UNUSED(param);
    m_webSocketServer = new QWebSocketServer(serverName, QWebSocketServer::NonSecureMode);
}

WebsocketServer::~WebsocketServer()
{
    m_webSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void WebsocketServer::stopListen()
{
    m_webSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

bool WebsocketServer::setTextSend(bool textSend)
{
    text_send_ = textSend;
}

void WebsocketServer::startListen(xxWebSocketServer_Listen_Param param)
{
    if(m_webSocketServer->isListening())
    {
        return ;
    }
    if(m_webSocketServer->listen(QHostAddress::Any, quint16(param.port)))
    {
        connect(m_webSocketServer, &QWebSocketServer::newConnection,
                this, &WebsocketServer::slotNewConnection);
        emit signalListened();
    }
}

qint64 WebsocketServer::slotBinarySend(QObject* client, const QByteArray& data)
{
    QWebSocket* pclient = static_cast<QWebSocket*>(client);
    bool found = false;
    for(int i = 0; (pclient != NULL) && i < m_clients.size(); i++)
    {
        if(pclient == m_clients.at(i))
        {
            found = true;
            break;
        }
    }
    qint64 send_len = 0;
    if(found)
    {
        send_len = sendDataByProtocolType(pclient, data, frames[pclient].m_protocol_type);
    }
    else
    {
        for(int i = 0; i < m_clients.size(); i++)
        {
            QWebSocket* pclient = m_clients.at(i);
            send_len = sendDataByProtocolType(pclient, data, frames[pclient].m_protocol_type);
        }
    }
    return send_len;
}

qint64 WebsocketServer::slotTextSend(QObject* client, const QString& data)
{
    return slotBinarySend(client, data.toUtf8());
}

void WebsocketServer::slotNewConnection()
{
    QWebSocket* client = m_webSocketServer->nextPendingConnection();

    connect(client, &QWebSocket::binaryFrameReceived, this, &WebsocketServer::slotClientBinaryFrameReceived);
    connect(client, &QWebSocket::textFrameReceived, this, &WebsocketServer::slotClientTextFrameReceived);
    connect(client, &QWebSocket::disconnected, this, &WebsocketServer::slotDisconnected);

    m_clients << client;
    emit signlNewConnected(client->peerAddress().toString(), client->peerPort());
    emit signlNewConnectedObj(client);
}

void WebsocketServer::slotClientBinaryFrameReceived(const QByteArray& frame, bool isLastFrame)
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());

    frames[pClient].m_protocol_type = (frames[pClient].m_protocol_type | 0x01);
    frames[pClient].m_recv_msg_cached.append(frame);
    if(true == isLastFrame)
    {
        emit signalBinaryData(pClient, frames[pClient].m_recv_msg_cached);
        frames[pClient].m_recv_msg_cached.clear();
    }
}

void WebsocketServer::slotClientTextFrameReceived(const QString& message, bool isLastFrame)
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    frames[pClient].m_recv_msg_cached.append(message.toUtf8());
    frames[pClient].m_protocol_type = (frames[pClient].m_protocol_type | 0x02);
    if(true == isLastFrame)
    {
        emit signalTextData(pClient, frames[pClient].m_recv_msg_cached);
        frames[pClient].m_recv_msg_cached.clear();
    }
}

void WebsocketServer::slotDisconnected()
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    if(pClient)
    {
        m_clients.removeAll(pClient);
        frames.remove(pClient);
        pClient->deleteLater();
    }

    emit signlNewNoConnectedObj(pClient);
}

qint64 WebsocketServer::sendDataByProtocolType(QObject* cient, const QByteArray& data_array, const unsigned char protocol_type)
{
    qint64 send_len = 0;
    QWebSocket* pClient = qobject_cast<QWebSocket*>(cient);
    if(protocol_type == 0x02 || text_send_)
    {
        send_len = pClient->sendTextMessage(data_array);
    }
    else
    {
        if(protocol_type == 0x03)
        {
            send_len = pClient->sendTextMessage(data_array);
            send_len = pClient->sendBinaryMessage(data_array);
        }
        else
        {
            send_len = pClient->sendBinaryMessage(data_array);
        }
    }
    return send_len;
}
