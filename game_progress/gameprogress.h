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
    void stopThread();

signals:
    /**
     * @brief 江湖定时器超时信号
     */
    void SignalJianghuTimeOut();

protected:
    void run();

private:
    GameProgress();
    GameProgress(const GameProgress&) = delete;  // 禁用拷贝构造函数
    GameProgress& operator=(const GameProgress&) = delete;  // 禁用赋值运算符
    static QMutex mutex;  // 互斥锁

    static GameProgress* instance;  // 单例对象指针
    bool m_stopRequested = false;   // 线程停止

    QTimer* jianghu_timer_; // 江湖定时器对象
    int anecdotes_time_ = 1000;    // 江湖轶事倒计时10秒
};

#endif // GAMEPROGRESS_H
