#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QAbstractSocket>
#include <QNetworkInterface>
#include <QMutex>
#include "public/public_macro.h"
#include "public/public_type.h"
#include "logger/logger.h"


/**
 * @brief 网络控制类
 */
class TcpClient : public QObject
{
    Q_OBJECT

    //指令返回状态/结果
    enum TcpStatusType
    {
        kConfirm  = 0, //确认
        kNegative = 1, //拒绝
        kUnknow   = 2, //未知/自定义
    };
public:
    explicit TcpClient(QObject* parent = nullptr);

signals:

public slots:
    /**
     * @brief 网络连接槽函数
     */
    void SlotTcpConnect();

    /**
     * @brief 连接成功处理函数
     */
    void SlotConnected();

    /**
     * @brief 读Socket数据槽函数
     * @return 无
     * @note 1.Socket的readyRead()触发后调用此函数读数据，在调用处理函数进行处理。
     *       2.此函数是网络数据的入口
     */
    void SlotTcpRead();

private:
    /**
     * @brief 是否连接成功
     */
    bool IsConnected();

    /**
     * @brief 生成时间戳
     */
    QString GenerateTimeStamp();

    /**
     * @brief 发送TCP数据
     */
    qint64 TcpWrite(QJsonObject& json_data);

    /**
     * @brief 收到服务器后回复
     */
    void JsonDataDeal(const QByteArray& json_data);

    /**
     * @brief JsonDataCheck 拼接数据检查
     * @param data 数据
     * @return
     */
    QByteArray JsonDataCheck(QByteArray data);

    /**
     * @brief 分割网络Json包函数
     * @param package_data：Json包的字节流数据
     * @return 分割好的Json包字节流列表
     * @note 1.该函数能缓解网络收发数据时多个Json包首尾连在一起的问题。
     */
    QList<QByteArray> DividePackage(QByteArray& package_data);

    /**
     * @brief 获取本地IP地址
     */
    QString GetLocalIpAddress();

    // 网络标记刷新定时器
    QTimer* net_status_timer_ = nullptr;

    //TCP断网后重连超时值，单位毫秒(ms)
    const int kTcpReconnectTimeoutVal_ = 6000;
    //TCP断网后重连超时值(短)，单位毫秒(ms)
    const int kTcpReconnectTimeoutValShort_ = 5000;
    //TCP重连报错阈值，单位次，每kTcpReconnectTimeoutVal_秒一次。
    const int kTcpReconnectWarnVal_ = 10;
    //最大接收的Json数据，超过的将丢弃。单位字节(byte)
    const int kTcpMaxJsonDataSize_ = 102400;
    //最大备份网络数据包数目（不包括心跳包和连接请求包）
    const int kTcpMaxJsonBackupNum = 50;
    //服务器名称（接收方字段值）
    const QString kServerName_ = "TIANGONG";
    //客户端名称（发送方字段值）
    const QString kClientName_ = "XIANREN";
    //允许连接控制（由连接请求指令的返回状态获得，如果不为“00”认定服务器拒绝通信，不再重连）
    QString connect_ctrl_ = "00";
    //对于不完整的数据保留，直到组成完整的数据
    QByteArray data_keeper_;
    //心跳包输出打印计数
    uint heart_beat_count_ = 0;

    //发数据锁
    QMutex send_data_mutex_;

    //UUID保存（相同ID字段值不进行处理）
    QString user_uuid_;

    //用户IP地址
    QString user_ip_;

    //连接成功标志位
    bool connect_ok_ = false;

    //服务器通信端口
    int server_port_ = MAIN_SERVER_PORT;

    //网络通信套接字
    QTcpSocket* tcp_socket_ = nullptr;
};

#endif // TCP_CLIENT_H
