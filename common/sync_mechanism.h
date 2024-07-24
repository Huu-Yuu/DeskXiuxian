#ifndef SYNC_MECHANISM_H
#define SYNC_MECHANISM_H

#include <QList>
#include <QJsonObject>
#include <QMutex>
#include <QMap>
#include <QObject>
#include <QVector>

typedef struct SyncMechanismDataSt_
{
    int time_out;///< 超时时间，单位ms
    long long save_time;///< 记录时间
    QVector<QString> ids;
    QVector<QJsonObject> send;
    QVector<QJsonObject> result;
    void* user;
    bool func_use;
    std::function<void (QVector<QJsonObject> send_list, QVector<QJsonObject> result_list, void*)> func;
} SyncMechanismDataSt;

typedef enum SyncMechanismRetEn_
{
    SyncMechanismRetSuccess = 0,
    SyncMechanismRetTimeout,
    SyncMechanismRetCancel
} SyncMechanismRetEn;


///< 支持多线程调用
class SyncMechanism
{
public:
    SyncMechanism();
    ~SyncMechanism();
    ///< 阻塞死等结果返回-- 0:成功 1:超时 2:取消
    int Wait(QJsonObject& obj, std::function<void (QJsonObject send)> func, std::function<bool ()> cancel, int t = 10000);
    ///< 非阻塞等结果回调返回
    void SyncWait(QVector<QJsonObject>& sends, void* user, int t, std::function<void (QVector<QJsonObject> send_list, QVector<QJsonObject> result_list, void*)> func_response);
    ///< 收到报文返回调用，obj对象为空表示检查超时报文回调
    bool SyncResponse(QJsonObject obj = QJsonObject(), QString cmd = "");
    ///< 阻塞死等条件返回 0:成功，1:超时
    int WaitAlways(std::function<bool (QString)> func, QString id = "", int t = 1000);
    ///< 阻塞死等条件返回 0:成功， 1:超时 2:取消
    int WaitAlwaysJsonObject(QJsonObject& obj, std::function<bool (QString, QJsonObject&)> func, std::function<bool ()> cancel, QString id, int t = 3000);
    ///< clear
    int Clear();

    int SyncWait(QJsonObject obj, std::function<void(QJsonObject)> func_response, int t = 3000);

private:
    ///< 增加一条
    void AddOneSyncMechanismData(SyncMechanismDataSt& one, QString id = "");
    ///< 判断id是否是否在vector中
    bool IdIsInVector(QVector<QString>& ids, QString id);
    bool CmdIsInVector(QVector<QJsonObject>& ids, QString cmd);
    QJsonObject GetOneSyncMechanismData(QString id);
private:
    QMap<QString, SyncMechanismDataSt> save_data_;
    QMutex save_data_mutex_;
};






#endif
