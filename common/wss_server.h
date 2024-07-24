#ifndef MY_WSS_SERVER_H
#define MY_WSS_SERVER_H
#include <QJsonObject>
#include <QMutex>
#include <QThread>
#include <QQueue>
#include <QMap>
#include "web_socket_server.h"

/**
 * @brief The WssServer class
 * WssServer 对象收发数据在一个独立的线程中
 *  使用步骤：
 * 1.构建对象
 * 2.Init
 * 3.收发数据
 * 4.销毁对象
 */

class WssServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief WssServer
     * @param log_name 收发数据打印日志文件名
     * @param port  端口
     * @param func  接收客户端数据回调，在独立的线程
     * @param ssl_type 是否加密
     */
    WssServer(QString log_name, int port, std::function<void (QObject* client, const QString& obj)> func, ST_SSL_TYPE ssl_type = ST_SSL_TYPE::kSSL_Close);
    ~WssServer();

    void setTextSend(bool textsend);
    /**
     * @brief 初始化
     */
    void Init();
    /**
     * @brief 发送数据 线程安全
     * @param client 客户端句柄
     * @param qs 报文
     * @return
     */
    bool Send(QObject* client, QString qs);
    /**
     * @brief 获取客户端个数
     * @return
     */
    int ClientNum();
    ///< 获取客户端列表
    QVector<QObject*> GetClientList();
signals:
    void signalStart();
    bool signalSend(QObject* client, QString qs);
private slots:
    void slotStart();
    bool slotSend(QObject* client, QString qs);
    void RecvData(QObject* client, const QString& data);
    void RecvDataByte(QObject* client, const QByteArray& data);
private:
    bool text_send_ = false;
    QString log_name_;///< 日志名字
    int port_;///< 端口
    ST_SSL_TYPE ssl_type_;///< ssl 类型
    std::function<void (QObject* client, const QString& obj)> func_;
    WebsocketServer* wss_server_ = nullptr;
    QThread thread_;
    QVector<QObject*> clients_;
    QMutex clients_mutex_;
};




#endif
