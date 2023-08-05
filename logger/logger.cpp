#include "logger.h"

QMutex Logger::mutex_;  // 初始化互斥锁对象
Logger* Logger::instance = nullptr;  // 初始化单例对象指针

Logger* Logger::GetInstance()
{
    if (!instance) {
        QMutexLocker locker(&mutex_);  // 加锁
        if (!instance) {
            instance = new Logger();
        }
    }
    return instance;
}
Logger::Logger(QObject *parent) : QObject(parent)
{
    // 创建日志文件夹（如果不存在）
    QDir logDir(QDir::currentPath() + "/log");
    if (!logDir.exists())
    {
        logDir.mkpath(".");
    }

    // 获取当前日期作为日志文件名
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString logFileName = logDir.filePath(currentDateTime + ".log");

    // 打开日志文件
    logFile_.setFileName(logFileName);
    if (logFile_.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        // 创建日志输出流
        logStream_.setDevice(&logFile_);

        // 启动日志记录线程
        thread_.start();
    }
    else
    {
        qDebug() << "Failed to open log file:" << logFile_.errorString();
    }
}

Logger::~Logger()
{
    // 等待日志记录线程结束
    thread_.quit();
    thread_.wait();

    // 关闭日志文件
    logFile_.close();
}

void Logger::log(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
//    QMutexLocker locker(&mutex_);
    // 获取当前时间戳
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 根据日志类型选择前缀
    QString prefix;
    switch (type)
    {
        case QtDebugMsg:
            prefix = "Debug";
            break;
        case QtWarningMsg:
            prefix = "Warning";
            break;
        case QtCriticalMsg:
            prefix = "Critical";
            break;
        case QtFatalMsg:
            prefix = "Fatal";
            break;
        case QtInfoMsg:
            prefix = "info";
            break;
        default:
            break;
    }
    // 获取文件名、函数名和行号等上下文信息
    QString fileName = context.file;
    QString functionName = context.function;
    int lineNumber = context.line;

    // 构造完整的日志信息
    QString logMessage = QString("[%1] [%2] [%3:%4 %5()] %6\n")
            .arg(timeStamp, prefix, fileName, QString::number(lineNumber), functionName, message);

    // 将日志信息写入文件
    logStream_ << logMessage;
    logStream_.flush();

    // 在控制台输出日志信息
    qDebug().noquote() << logMessage;
}
