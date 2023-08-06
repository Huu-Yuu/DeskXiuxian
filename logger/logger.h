#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QThread>
#include <QMutex>

/**
 * @brief 日志记录器
 */
class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger* GetInstance();

    ~Logger();

signals:

public slots:
    void SlotOutTolog(QtMsgType type, const QMessageLogContext& context, const QString& message);

private:
    explicit Logger(QObject *parent = nullptr);
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    static Logger* instance;  // 单例对象指针
    QFile logFile_;
    QTextStream logStream_;
    QThread thread_;
    static QMutex mutex_; // 互斥锁，用于线程同步
};

#endif // LOGGER_H
