#include "gameprogress.h"

QMutex GameProgress::mutex;  // 初始化互斥锁对象
GameProgress* GameProgress::instance = nullptr;  // 初始化单例对象指针

GameProgress::GameProgress()
{

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

        eventLoop.exec();
    }

    // 线程停止后执行清理工作
    // ...
}
