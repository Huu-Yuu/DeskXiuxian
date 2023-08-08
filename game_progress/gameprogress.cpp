#include "gameprogress.h"

QMutex GameProgress::mutex;  // 初始化互斥锁对象
GameProgress* GameProgress::instance = nullptr;  // 初始化单例对象指针

GameProgress::~GameProgress()
{
    jianghu_timer_->stop();
    delete jianghu_timer_;
    jianghu_timer_ = NULL;
}

GameProgress::GameProgress()
{
    // 定时器开始
    jianghu_timer_ = new QTimer;
    // 写入江湖事件循环事件，非单次循环
    jianghu_timer_->setInterval(anecdotes_time_);
    jianghu_timer_->setSingleShot(false);
    jianghu_timer_->start();

    qDebug() << "游戏进程控制类 线程ID：" << currentThreadId();

    // 将定时器信号与类信号链接
    connect(jianghu_timer_, SIGNAL(timeout()), this, SIGNAL(SignalJianghuTimeOut()));
}

GameProgress* GameProgress::GetInstance()
{
    if (!instance)
    {
        QMutexLocker locker(&mutex);  // 加锁
        if (!instance) {
            instance = new GameProgress();
        }
    }
    return instance;
}

void GameProgress::stopThread()
{
    m_stopRequested = true;
}

void GameProgress::run()
{
    // 创建一个事件循环对象
    QEventLoop eventLoop;
    // 在事件循环中执行线程逻辑
    while (!m_stopRequested) {

//        eventLoop.exec();
    }

    // 线程停止后执行清理工作
    // ...
    m_stopRequested = false;
}

QTimer* GameProgress::GetJianghuTimer()
{
    return jianghu_timer_;
}

void GameProgress::SetAnecdotesTime_(int time)
{
    anecdotes_time_ = time;
}
