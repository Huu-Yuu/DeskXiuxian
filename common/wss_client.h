#ifndef MY_WSS_CLIENT_H
#define MY_WSS_CLIENT_H
#include <QJsonObject>
#include <QMutex>
#include <QThread>
#include <QQueue>
#include <QMap>
#include "web_socket_client.h"
#include "my_std_thread.h"

/**
 * @brief The WssClient class
 * WssClient 对象收发数据在一个独立的线程中
 *  使用步骤：
 * 1.构建对象
 * 2.Init
 * 3.收发数据
 * 4.销毁对象
 */

class WssClient : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief WssClient
     * @param log_name 收发数据打印日志文件名
     * @param url 服务端url
     * @param func 接收服务端数据回调，在独立的线程
     * @param ping 是否ping
     * @param ssl_type 是否加密
     * @param param 加密证书文件地址（绝对路径）
     */
    WssClient(QString log_name, QString url, std::function<void (const QByteArray& obj)> func, bool ping,
              ST_SSL_TYPE ssl_type = ST_SSL_TYPE::kSSL_Close, QStringList param = QStringList());
    ~WssClient();
    /**
     * @brief 初始化
     */
    void Init();
    /**
     * @brief 发送数据 线程安全
     * @param qs 报文
     * @return
     */
    bool Send(QByteArray qs);
    /**
     * @brief 是否连接成功
     * @return
     */
    bool GetConnected();
signals:
    void signalStart();
    bool signalSend(QByteArray qs);
    void signalPing();
    void signalConnectedStatus(int status);
private slots:
    void slotStart();
    bool slotSend(QByteArray qs);
    void slotPing();
    void RecvData(const QByteArray& data);
    void slotMessageReceive(const QByteArray& frame, bool isLastFrame);
private:
    void SetConnected(bool con);
    void PthreadSelf(void* msg);
private:
    QString log_name_;///< 日志名字
    QString url_;///< 端口
    bool ping_;///< 是否ping
    ST_SSL_TYPE ssl_type_;///< ssl 类型
    QStringList ssl_cert_addr_;///< 证书地址
    std::function<void (const QByteArray& obj)> func_;
    WebsocketClient* wss_client_ = nullptr;
    QThread thread_;
    bool is_connected_ = false;
    QMutex is_connected_mutex_;
    MyStdThread my_thread_;
};




#endif
