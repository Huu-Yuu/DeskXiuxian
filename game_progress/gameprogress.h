#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QEventLoop>
#include <QTimer>
#include "role/rolesystem.h"

/**
 * @brief 游戏进程控制类
 */
class GameProgress : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief 单例
     */
    static GameProgress* GetInstance();

    ~GameProgress();

    /**
     * @brief 获取基本事件循环时间
     */
    int GetAnecdotesTime();

    /**
     * @brief 获取属性事件循环时间
     */
    int GetAttTime();

    /**
     * @brief 单例
     */
    QTimer* GetJianghuTimer();

    /**
     * @brief 写入江湖轶事倒计时
     */
    void SetAnecdotesTime_(int time);

    /**
     * @brief 停止线程
     */
    void StopThread();

    /**
     * @brief 开启修行事件定时器
     */
    void StarPractic();

    /**
     * @brief 暂停修行事件定时器
     */
    void StopPractic();

signals:
    /**
     * @brief 江湖定时器超时信号
     */
    void SignalJianghuTimeOut();

    /**
     * @brief 基本属性定时器超时信号
     */
    void SignalBasicAttTimeOut();

    /**
     * @brief 角色寿命成长定时器超时信号
     */
    void SignaleLifeUpdataTimeOut();

protected:
    void run();

private:
    GameProgress();
    GameProgress(const GameProgress&) = delete;  // 禁用拷贝构造函数
    GameProgress& operator=(const GameProgress&) = delete;  // 禁用赋值运算符
    static QMutex mutex;  // 互斥锁

    static GameProgress* instance;  // 单例对象指针
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
