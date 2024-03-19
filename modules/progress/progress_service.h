#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QEventLoop>
#include <QTimer>
#include "modules/role/role_player.h"
#include "common/singleton.h"

/**
 * @brief 游戏进程管理类
 */
class ProgressService : public QThread
{
    Q_OBJECT

public:
    SINGLETON(ProgressService);
    ProgressService();
    ~ProgressService();

    int GetAnecdotesTime(); ///< 获取基本事件循环时间

    int GetAttTime();   ///< 获取属性事件循环时间


    QTimer* GetJianghuTimer();  ///< 获取江湖定时器
    void SetAnecdotesTime_(int time);   ///< 写入江湖轶事倒计时
    void StopThread();  ///< 停止线程
    void StarPractic();     ///< 开启修行事件定时器
    void StopPractic();     ///< 暂停修行事件定时器

signals:

    void SignalJianghuTimeOut();    ///< 江湖定时器超时信号
    void SignalBasicAttTimeOut();   ///< 基本属性定时器超时信号
    void SignaleLifeUpdataTimeOut();    ///< 角色寿命成长定时器超时信号

    //请求外部动作
    void SignalActionRequest(const QJsonObject& request_data);
    //本模块动作执行结果抛给上一级
    void SignalActionResponse(const QJsonObject& request_data);
    //状态变化抛给上一级
    void SignalPubTopic(const QJsonObject& pub_data);

public slots:
    void SlotCyclicLifeUpdate();   ///< 寿命更新
    void SlotCyclicCultivation();   ///< 循环修炼
    void SlotCyclicBasicAtt();      ///< 循环增加基本属性

protected:
    void run();

private:
    static QMutex mutex;  // 互斥锁
    bool m_stopRequested = false;   // 线程停止

    QTimer* jianghu_timer_;         // 江湖定时器对象  影响 经验值和货币
    int anecdotes_time_ = 10000;    // 江湖轶事倒计时10秒
    int anecdotes_time_factor_;          // 倒计时系数

    QTimer* basic_att_timer_;       // 基本属性定时器 影响 攻击防御血量
    int att_time_ = 20000;           // 基本属性事件倒计时 20秒
    int att_time_factor_;           // 倒计时系数

    QTimer* life_timer_;            // 角色寿命计时器
};

#endif // GAMEPROGRESS_H
