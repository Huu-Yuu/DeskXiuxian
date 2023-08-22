#include "gameprogress.h"

QMutex GameProgress::mutex;  // 初始化互斥锁对象
GameProgress* GameProgress::instance = nullptr;  // 初始化单例对象指针

GameProgress::~GameProgress()
{
    jianghu_timer_->stop();
    if (jianghu_timer_ != NULL)
        delete jianghu_timer_;
    jianghu_timer_ = NULL;

    basic_att_timer_->stop();
    if(basic_att_timer_ != NULL)
        delete basic_att_timer_;
    basic_att_timer_ = NULL;

    life_timer_->stop();
    if(life_timer_ != NULL)
        delete life_timer_;
    life_timer_ = NULL;
}

GameProgress::GameProgress()
{
    // 定时器开始
    jianghu_timer_ = new QTimer;
    basic_att_timer_ = new QTimer;
    life_timer_ = new QTimer;

    // 开始增加寿命
    life_timer_->setInterval(1000);
    life_timer_->setSingleShot(false);

    // 写入江湖事件循环事件，非单次循环，影响经验值和货币
    jianghu_timer_->setInterval(anecdotes_time_);
    jianghu_timer_->setSingleShot(false);

    // 写入基本属性事件循环事件，非单次循环，影响攻防血
    basic_att_timer_->setInterval(att_time_);
    basic_att_timer_->setSingleShot(false);

    // 将定时器信号与类信号链接
    connect(jianghu_timer_, SIGNAL(timeout()), this, SIGNAL(SignalJianghuTimeOut()));
    connect(basic_att_timer_, SIGNAL(timeout()), this, SIGNAL(SignalBasicAttTimeOut()));
    connect(life_timer_, SIGNAL(timeout()), this, SIGNAL(SignaleLifeUpdataTimeOut()));

    qDebug() << "游戏进程控制类 线程ID：" << currentThreadId();
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

int GameProgress::GetAnecdotesTime()
{
    return anecdotes_time_;
}

int GameProgress::GetAttTime()
{
    return att_time_;
}

void GameProgress::StarPractic()
{
    life_timer_->start();
    jianghu_timer_->start();
    basic_att_timer_->start();
}

void GameProgress::StopPractic()
{
    life_timer_->stop();
    jianghu_timer_->stop();
    basic_att_timer_->stop();
}

void GameProgress::StopThread()
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
