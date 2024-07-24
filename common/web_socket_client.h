#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QThread>
#include <QMutex>
#include <QTimer>
#include "web_socket_define.h"


class WebsocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketClient(const QString& address, ST_SSL_TYPE ssl_type = ST_SSL_TYPE::kSSL_Close, QStringList param = QStringList());

    ~WebsocketClient();
    void SetReconnectTime(int timeout);
public slots:
    /**
     * @brief onDataSend 发送数据
     * @param data 数据
     */
    qint64 onBinarySend(const QByteArray& data);

    qint64 onTextSend(const QString& data);

    void Ping(QByteArray data);
signals:
    /**
     * @brief binaryFrameReceived 接收数据
     * @param frame 数据
     * @param isLastFrame 是否最后一帧
     */
    void signalBinaryFrameReceived(const QByteArray& frame, bool isLastFrame);
    void signalTextFrameReceived(const QString& frame, bool isLastFrame);
    void signalConnected();
    void signalDisconnected();

protected:
    void DebugOutput(const QString& content, int level = 1);

private slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError);
    void onBinaryFrameReceived(const QByteArray& frame, bool isLastFrame);
    void OnTextFrameReceived(const QString& frame, bool isLastFrame);
    void onPing(const QByteArray& content);
    void onPong(quint64 elapsedTime, const QByteArray& payload);

private:
    QWebSocket* m_webSocket_ = nullptr;
    QTimer timer_;
    QUrl m_url_;
    const int timer_timeout_ = 5000;
    int reconnect_time_without_data_ = 20000;
};

#endif // WEBSOCKETCLIENT_H
