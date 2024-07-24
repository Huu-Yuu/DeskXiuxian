#ifndef WEB_SOCKET_SERVER_H
#define WEB_SOCKET_SERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QTimer>
#include "web_socket_client.h"

typedef struct xxWebSocketServer_Listen_Param
{
    quint16 port;
    QByteArray addr;
} WebSocketServer_Listen_Param;


typedef struct xxWebsocketServer_Request_Context
{
    unsigned char m_protocol_type = 0; /*消息类型，0x01: 二进制，0x02:文本，0x03:文本和二进制，其他为二进制 */
    QByteArray m_recv_msg_cached = "";/*消息内容，只有等到消息完整才会向应用投递信息到来*/
} WebsocketServer_Request_Context;

class WebsocketServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief WebsocketServer 构造一个websocket服务
     * @param serverName 服务名称，仅做日志记录
     * @param ssl_type 是否需要添加ssl协议
     * @param param ssl协议的辅助参数，当ssl类型为单向或者双向证书
     */
    explicit WebsocketServer(const QString& serverName,  ST_SSL_TYPE ssl_type = ST_SSL_TYPE::kSSL_Close, QStringList param = QStringList());

    ~WebsocketServer();

    /**
     * @brief startListen 开始监听端口
     * @param param 设定监听的ip和端口
     */
    void startListen(WebSocketServer_Listen_Param param);
    void stopListen();

    bool setTextSend(bool textSend);
public slots:
    /**
     * @brief slotBinarySend
     * @param socket_id 发送给哪一个socket，-1,表示发给连接的所有的client
     * @param data 要发送的二进制数据
     * @return 发送的长度，发送成功，则和data的长度一致
     */
    qint64 slotBinarySend(QObject* client, const QByteArray& data);

    /**
     * @brief slotTextSend
     * @param socket_id 发送给哪一个socket，-1,表示发给连接的所有的client
     * @param data 要发送的文本数据
     * @return 发送的长度，发送成功，则和data的长度一致
     */
    qint64 slotTextSend(QObject* client, const QString& data);

signals:
    /**
     * @brief slotListened 启动监听完成
     */
    void signalListened();

    /**
     * @brief signlNewConnected 收到新的网络连接
     * @param per_addr
     * @param peer_port
     */
    void signlNewConnected(QString per_addr, int peer_port);

    void signlNewConnectedObj(QObject* client);
    void signlNewNoConnectedObj(QObject* client);
    /**
     * @brief signalBinaryData 收到的二进制数据
     * @param client
     * @param data
     */
    void signalBinaryData(QObject* client, const QByteArray& data);
    /**
     * @brief signalTextData 收到的文本数据
     * @param client
     * @param data
     */
    void signalTextData(QObject* client, const QString& data);

private slots:
    /**
     * @brief slotNewConnection 新的连接到来
     */
    void slotNewConnection();

    /**
     * @brief slotClientBinaryFrameReceived 处理接收的二进制数据
     * @param frame 一帧数据
     * @param isLastFrame 是否是最后一帧
     */
    void slotClientBinaryFrameReceived(const QByteArray& frame, bool isLastFrame);
    /**
     * @brief slotClientTextFrameReceived 处理接收的文本数据
     * @param frame 一帧数据
     * @param isLastFrame 是否是最后一帧
     */
    void slotClientTextFrameReceived(const QString& text, bool isLastFrame);

    /**
     * @brief slotDisconnected 客户端断开处理
     */
    void slotDisconnected();

private:
    qint64 sendDataByProtocolType(QObject* cient, const QByteArray& data_array, const unsigned char msg_type);
private:
    QWebSocketServer* m_webSocketServer;
    int m_servePort = 9999;

    QList<QWebSocket*> m_clients;
    QMap<QObject*, WebsocketServer_Request_Context> frames;
    const bool m_debug = true;
    bool text_send_ = false;
};

#endif // WEB_SOCKET_SERVER_H
