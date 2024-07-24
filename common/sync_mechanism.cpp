#include "sync_mechanism.h"
#include <QDateTime>
#include <unistd.h>
#include <QUuid>
#include <QDebug>


SyncMechanism::SyncMechanism()
{
    save_data_.clear();
}
SyncMechanism::~SyncMechanism()
{

}

int SyncMechanism::Wait(QJsonObject& obj, std::function<void (QJsonObject send)> func, std::function<bool ()> cancel, int t)
{
    int ret = -1;
    QString id = obj.value("id").toString();
    SyncMechanismDataSt one;
    one.time_out = t;
    one.ids.push_back(id);
    one.send.push_back(obj);
    one.func_use = false;
    one.save_time = QDateTime::currentMSecsSinceEpoch();
    AddOneSyncMechanismData(one, id);
    ///< 放在此处目的，防止emit后立马返回数据，先保存数据
    func(obj);
    long long cur_t;
    while(1)
    {
        if(one.time_out > 0)
        {
            cur_t = QDateTime::currentMSecsSinceEpoch();
            if(cur_t < one.save_time)
            {
                one.save_time = cur_t;///< 重新计时
            }
            if((cur_t - one.save_time) > one.time_out)
            {
                ret = SyncMechanismRetTimeout;
                break;
            }
        }

        obj = GetOneSyncMechanismData(id);
        if(obj.size() > 0)
        {
            ret = SyncMechanismRetSuccess;
            break;
        }
        if(cancel())
        {
            ret = SyncMechanismRetCancel;
            break;
        }
        usleep(1000);
    }

    return ret;
}

int SyncMechanism::SyncWait(QJsonObject obj, std::function<void (QJsonObject)> func_response, int t)
{
    SyncMechanismDataSt one;
    QVector<QJsonObject> sends;
    sends.push_back(obj);
    one.time_out = t;
    for(int i = 0; i < sends.size(); i++)
    {
        one.ids.push_back(sends[i].value("id").toString());
    }
    one.send = sends;
    one.save_time = QDateTime::currentMSecsSinceEpoch();
    one.user = nullptr;
    one.func_use = true;
    std::function<void (QVector<QJsonObject> send_list, QVector<QJsonObject> result_list, void*)> func = [ = ](QVector<QJsonObject> send_list, QVector<QJsonObject> result_list, void*)
    {
        func_response(send_list[0]);
    };
    one.func = func;
    AddOneSyncMechanismData(one);
}

void SyncMechanism::SyncWait(QVector<QJsonObject>& sends, void* user, int t, std::function<void (QVector<QJsonObject> send_list, QVector<QJsonObject> result_list, void*)> func_response)
{
    SyncMechanismDataSt one;
    one.time_out = t;
    for(int i = 0; i < sends.size(); i++)
    {
        one.ids.push_back(sends[i].value("id").toString());
    }
    one.send = sends;
    one.save_time = QDateTime::currentMSecsSinceEpoch();
    one.user = user;
    one.func_use = true;
    one.func = func_response;
    AddOneSyncMechanismData(one);
}


bool SyncMechanism::SyncResponse(QJsonObject obj, QString cmd)
{
    bool ret = false;
    QString id = obj.value("id").toString();
    QMap<QString, SyncMechanismDataSt> callback;


    {
        QMutexLocker lock(&save_data_mutex_);
        for(auto it = save_data_.begin(); it != save_data_.end();)
        {
            if(cmd.length() > 0) ///< 命令字匹配，不是id匹配
            {
                if(CmdIsInVector(it->send, cmd))
                {
                    it->result.push_back(obj);
                }
            }
            else if(id.length() > 0 && IdIsInVector(it->ids, id)) ///<
            {
                qDebug() << "SyncMechanism::SyncResponse accept" << id;
                it->result.push_back(obj);
                ret = true;
            }
            long long t = QDateTime::currentMSecsSinceEpoch();
            if(t < it->save_time)
            {
                it->save_time = t;
            }
            if(it->time_out > 0 && t - it->save_time > it->time_out) ///< 超时触发回调
            {
                qDebug() << "SyncMechanism::SyncResponse timeout ";
                callback[it.key()] = *it;
                it = save_data_.erase(it);
                ret = true;
            }
            else if(it->send.size() <= it->result.size())///< 都返回了触发回调
            {
                if(it->func_use)
                {
                    callback[it.key()] = *it;
                    it = save_data_.erase(it);
                }
                break;
            }
            else
            {

                it++;
            }
        }
    }

    for(auto it = callback.begin(); it != callback.end(); it++)
    {
        if(it->func_use && it->func)
        {
            it->func(it->send, it->result, it->user);
            ret = true;
        }
    }

    return ret;
}


void SyncMechanism::AddOneSyncMechanismData(SyncMechanismDataSt& one, QString id)
{
    if(id.length() <= 0)
    {
        id = QUuid::createUuid().toString();
    }
    QMutexLocker lock(&save_data_mutex_);
    save_data_[id] = one;
}

bool SyncMechanism::CmdIsInVector(QVector<QJsonObject>& ids, QString cmd)
{
    bool ret = false;

    for(int i = 0; i < ids.size(); i++)
    {
        if(ids[i].value("type").toString() == cmd)
        {
            ret = true;
            break;
        }
    }

    return ret;
}

bool SyncMechanism::IdIsInVector(QVector<QString>& ids, QString id)
{
    bool ret = false;

    for(int i = 0; i < ids.size(); i++)
    {
        if(ids[i] == id)
        {
            ret = true;
            break;
        }
    }

    return ret;
}

QJsonObject SyncMechanism::GetOneSyncMechanismData(QString id)
{
    QJsonObject ret;
    QMutexLocker lock(&save_data_mutex_);
    if(save_data_.contains(id) && save_data_[id].result.size() > 0)
    {
        ret = save_data_[id].result[0];
        save_data_.remove(id);
    }

    return ret;
}

int SyncMechanism::WaitAlways(std::function<bool (QString id)> func, QString id, int t)  //以1000us为周期的循环判断延时 阻塞型
{
    int ret = -1;
    long long last_t = QDateTime::currentMSecsSinceEpoch();
    long long cur_t;
    while(1)
    {
        if(t > 0)
        {
            cur_t = QDateTime::currentMSecsSinceEpoch();
            if(cur_t < last_t)
            {
                last_t = cur_t;///< 重新计时
            }
            if((cur_t - last_t) > t)
            {
                ret = SyncMechanismRetTimeout;
                break;
            }
        }

        if(func(id))
        {
            ret = SyncMechanismRetSuccess;
            break;
        }
        usleep(1000);
    }

    return ret;
}

int SyncMechanism::WaitAlwaysJsonObject(QJsonObject& obj, std::function<bool (QString, QJsonObject&)> func, std::function<bool ()> cancel, QString id, int t)
{
    int ret = -1;
    long long last_t = QDateTime::currentMSecsSinceEpoch();
    long long cur_t;
    while(1)
    {
        if(t > 0)
        {
            cur_t = QDateTime::currentMSecsSinceEpoch();
            if(cur_t < last_t)
            {
                last_t = cur_t;///< 重新计时
            }
            if((cur_t - last_t) > t)
            {
                ret = SyncMechanismRetTimeout;
                break;
            }
        }

        if(func(id, obj))
        {
            ret = SyncMechanismRetSuccess;
            break;
        }
        if(cancel())
        {
            ret = SyncMechanismRetCancel;
            break;
        }
        usleep(1000);
    }

    return ret;
}

int SyncMechanism::Clear()
{
    QMutexLocker lock(&save_data_mutex_);
    save_data_.clear();
    return 0;
}


