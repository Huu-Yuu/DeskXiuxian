#include "logger.h"

QMutex Logger::mutex_;  // 初始化互斥锁对象
Logger* Logger::instance = nullptr;  // 初始化单例对象指针
QMutex Logger::std_log_mutex;

Logger* Logger::GetInstance()
{
    if (!instance)
    {
        QMutexLocker locker(&mutex_);  // 加锁
        if (!instance)
        {
            instance = new Logger();
        }
    }
    return instance;
}

Logger::Logger(QObject* parent) : QObject(parent)
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
        qDebug() << "无法打开日志文件:" << logFile_.errorString();
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

void Logger::SlotOutTolog(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
//    std_log_mutex.lock();
    // 获取当前时间戳
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 根据日志类型选择前缀
    QString prefix;
    switch (type)
    {
        case QtDebugMsg:
            prefix = "调试";
            break;
        case QtWarningMsg:
            prefix = "告警";
            break;
        case QtCriticalMsg:
            prefix = "关键";
            break;
        case QtFatalMsg:
            prefix = "致命";
            break;
        case QtInfoMsg:
            prefix = "消息";
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
//    std_log_mutex.unlock();
}

void Logger::OutputMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    std_log_mutex.lock();
    QString current_date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString current_time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString message;
    QString log_file_path;
    //程序可能会24小时运行不间断，日志需要按日期分开
    QString log_dir_path = "/log/";
    log_file_path = log_dir_path + current_date + "_upper.log";

    switch (type)
    {
        case QtDebugMsg:
        {
            message = QString("Debug   : \"%1 %2\" | %3")
                      .arg(current_date, current_time, msg);
            break;
        }
        case QtInfoMsg:
        {
            message = QString("Info  : \"%1 %2\" | %3")
                      .arg(current_date, current_time, msg);
            break;
        }
        case QtWarningMsg:
        {
            message = QString("Warning : \"%1 %2\" | %3")
                      .arg(current_date, current_time, msg);
            break;
        }
        case QtCriticalMsg:
        {
            message = QString("Critical: \"%1 %2\" | File \"%3\" Line %4 in"
                              " Func \"%5\" -> Msg: \"%6\"\n")
                      .arg(current_date, current_time, context.file)
                      .arg(context.line).arg(context.function, msg);
            break;
        }
        case QtFatalMsg:
        {
            message = QString("Fatal   : \"%1 %2\" | File \"%3\" Line %4 in"
                              " Func \"%5\" -> Msg: \"%6\"\n")
                      .arg(current_date, current_time, context.file)
                      .arg(context.line).arg(context.function, msg);
            break;
        }
    }

    QFile file(log_file_path);
    bool result = file.open(QIODevice::WriteOnly | QIODevice::Append |
                            QIODevice::Text);
    if (result == true)
    {
        QTextStream text_stream(&file);
        text_stream << message << endl;
        file.flush();
        file.close();
    }
    else
    {
        qDebug() << "Create Log File Failed！";
    }
    std_log_mutex.unlock();
}

int Logger::GetErrorBaseType(int error_code)
{
    return (error_code & ERROR_BASE_MASK);
}

int Logger::GetErrorBaseCode(int error_code)
{
    return (error_code & ERROR_CODE_MASK);
}

QString Logger::GetErrorTypeName(int error_type_base)
{
    int base_type = GetErrorBaseType(error_type_base);
    switch (base_type)
    {
        case ERROR_NETWORK_BASE:
            return "网络通信错误";
        case ERROR_NETFILE_BASE:
            return "网络文件传输错误";
        case ERROR_QSOCKET_BASE:
            return "网络套接字错误";
        default:
            return "未知错误类型";
    }
}

QString Logger::GetErrorDescription(int error_code)
{
    switch (error_code)
    {
        case NO_ERROR:
            return tr("NO_ERROR");

        case ERROR_AIUI_MSP_INVALID_PARA:
            return tr("ERROR_AIUI_MSP_INVALID_PARA");
        case ERROR_AIUI_MSP_INVALID_PARA_VALUE:
            return tr("ERROR_AIUI_MSP_INVALID_PARA_VALUE");
        case ERROR_AIUI_MSP_NOT_FOUND:
            return tr("ERROR_AIUI_MSP_NOT_FOUND");
        case ERROR_AIUI_NO_RESPONSE_DATA:
            return tr("ERROR_AIUI_NO_RESPONSE_DATA");
        case ERROR_AIUI_MSP_LMOD_RUNTIME_EXCEPTION:
            return tr("ERROR_AIUI_MSP_LMOD_RUNTIME_EXCEPTION");
        case ERROR_AIUI_NO_NETWORK:
            return tr("ERROR_AIUI_NO_NETWORK");
        case ERROR_AIUI_NETWORK_TIMEOUT:
            return tr("ERROR_AIUI_NETWORK_TIMEOUT");
        case ERROR_AIUI_NET_EXPECTION:
            return tr("ERROR_AIUI_NET_EXPECTION");
        case ERROR_AIUI_INVALID_RESULT:
            return tr("ERROR_AIUI_INVALID_RESULT");
        case ERROR_AIUI_NO_MATCH:
            return tr("ERROR_AIUI_NO_MATCH");
        case ERROR_AIUI_AUDIO_RECORD:
            return tr("ERROR_AIUI_AUDIO_RECORD");
        case ERROR_AIUI_COMPONENT_NOT_INSTALLED:
            return tr("ERROR_AIUI_COMPONENT_NOT_INSTALLED");
        case ERROR_AIUI_SERVICE_BINDER_DIED:
            return tr("ERROR_AIUI_SERVICE_BINDER_DIED");
        case ERROR_AIUI_LOCAL_NO_INIT:
            return tr("ERROR_AIUI_LOCAL_NO_INIT");
        case ERROR_AIUI_UNKNOWN:
            return tr("ERROR_AIUI_UNKNOWN");

        case ERROR_NETWORK_BASE:
            return tr("ERROR_NETWORK_BASE");
        case ERROR_NETWORK_DISCONNECTED:
            return tr("ERROR_NETWORK_DISCONNECTED");
        case ERROR_NETWORK_HEAD_NOT_MATCH:
            return tr("ERROR_NETWORK_HEAD_NOT_MATCH");
        case ERROR_NETWORK_UUID_NOT_MATH:
            return tr("ERROR_NETWORK_UUID_NOT_MATH");
        case ERROR_NETWORK_UNKNOW_CMAD:
            return tr("ERROR_NETWORK_UNKNOW_CMAD");
        case ERROR_NETWORK_REQUEST_REJECT:
            return tr("ERROR_NETWORK_REQUEST_REJECT");
        case ERROR_NETWORK_RESEND_OVERTIMES:
            return tr("ERROR_NETWORK_RESEND_OVERTIMES");
        case ERROR_NETWORK_COMMU_REFUSE:
            return tr("ERROR_NETWORK_COMMU_REFUSE");
        case ERROR_NETWORK_HEAD_NOT_VAILD:
            return tr("ERROR_NETWORK_HEAD_NOT_VAILD");


        case ERROR_NETFILE_BASE:
            return tr("ERROR_NETFILE_BASE");
        case ERROR_NETFILE_DISCONNECTED:
            return tr("ERROR_NETFILE_DISCONNECTED");
        case ERROR_NETFILE_DIR_CREATE:
            return tr("ERROR_NETFILE_DIR_CREATE");
        case ERROR_NETFILE_SEND_FILE_NOT_EXIST:
            return tr("ERROR_NETFILE_SEND_FILE_NOT_EXIST");
        case ERROR_NETFILE_SEND_FILE_OPEN:
            return tr("ERROR_NETFILE_SEND_FILE_OPEN");
        case ERROR_NETFILE_SEND_CONTENT:
            return tr("ERROR_NETFILE_SEND_CONTENT");
        case ERROR_NETFILE_SEND_NOT_MATCH:
            return tr("ERROR_NETFILE_SEND_NOT_MATCH");
        case ERROR_NETFILE_FILE_NOT_READABLE:
            return tr("ERROR_NETFILE_FILE_NOT_READABLE");
        case ERROR_NETFILE_RECV_FILE_NOT_EXIST:
            return tr("ERROR_NETFILE_RECV_FILE_NOT_EXIST");
        case ERROR_NETFILE_RECV_FILE_OPEN:
            return tr("ERROR_NETFILE_RECV_FILE_OPEN");
        case ERROR_NETFILE_RECV_CONTENT:
            return tr("ERROR_NETFILE_RECV_CONTENT");
        case ERROR_NETFILE_RECV_NOT_MATCH:
            return tr("ERROR_NETFILE_RECV_NOT_MATCH");
        case ERROR_NETFILE_FILE_NOT_WRITABLE:
            return tr("ERROR_NETFILE_FILE_NOT_WRITABLE");
        case ERROR_NETFILE_RECV_SIZE_NOT_MATCH:
            return tr("ERROR_NETFILE_RECV_SIZE_NOT_MATCH");
        case ERROR_NETFILE_RECV_UUID_NOT_MATCH:
            return tr("ERROR_NETFILE_RECV_UUID_NOT_MATCH");

        case ERROR_NETFILE_WRITE_SOCKET:
            return tr("ERROR_NETFILE_WRITE_SOCKET");


        case ERROR_QSOCKET_BASE:
            return tr("ERROR_QSOCKET_BASE");
        case ERROR_QSOCKET_FILE:
            return tr("ERROR_QSOCKET_FILE");
        case ERROR_QSOCKET_REMOTE_HOST_CLOSE:
            return tr("ERROR_QSOCKET_REMOTE_HOST_CLOSE");
        case ERROR_QSOCKET_HOST_NOT_FOUND:
            return tr("ERROR_QSOCKET_HOST_NOT_FOUND");
        case ERROR_QSOCKET_ACCESS:
            return tr("ERROR_QSOCKET_ACCESS");
        case ERROR_QSOCKET_SOURCE_RAN_OUT:
            return tr("ERROR_QSOCKET_SOURCE_RAN_OUT");
        case ERROR_QSOCKET_TIMEOUT:
            return tr("ERROR_QSOCKET_TIMEOUT");
        case ERROR_QSOCKET_DATAGRAM_TOO_LARGE:
            return tr("ERROR_QSOCKET_DATAGRAM_TOO_LARGE");
        case ERROR_QSOCKET_NETWORK:
            return tr("ERROR_QSOCKET_NETWORK");
        case ERROR_QSOCKET_ACCESS_IN_USE:
            return tr("ERROR_QSOCKET_ACCESS_IN_USE");
        case ERROR_QSOCKET_ADDR_NOT_AVAILABLE:
            return tr("ERROR_QSOCKET_ADDR_NOT_AVAILABLE");
        case ERROR_QSOCKET_UNSUPPORT_OPERATION:
            return tr("ERROR_QSOCKET_UNSUPPORT_OPERATION");
        case ERROR_QSOCKET_PROXY_AUT_REQ:
            return tr("ERROR_QSOCKET_PROXY_AUT_REQ");
        case ERROR_QSOCKET_SSL_HANDSHAKE:
            return tr("ERROR_QSOCKET_SSL_HANDSHAKE");
        case ERROR_QSOCKET_UNFINISHED_OPERATION:
            return tr("ERROR_QSOCKET_UNFINISHED_OPERATION");
        case ERROR_QSOCKET_PROXY_CONNECT_REFUSE:
            return tr("ERROR_QSOCKET_PROXY_CONNECT_REFUSE");
        case ERROR_QSOCKET_PROXY_CONNECT_CLOSE:
            return tr("ERROR_QSOCKET_PROXY_CONNECT_CLOSE");
        case ERROR_QSOCKET_PROXY_CONNECT_TIMEOUT:
            return tr("ERROR_QSOCKET_PROXY_CONNECT_TIMEOUT");
        case ERROR_QSOCKET_PROXY_NOT_FOUND:
            return tr("ERROR_QSOCKET_PROXY_NOT_FOUND");
        case ERROR_QSOCKET_PROXY_PROTOCOL:
            return tr("ERROR_QSOCKET_PROXY_PROTOCOL");
        case ERROR_QSOCKET_OPERATION:
            return tr("ERROR_QSOCKET_OPERATION");
        case ERROR_QSOCKET_SSL_INTERNAL:
            return tr("ERROR_QSOCKET_SSL_INTERNAL");
        case ERROR_QSOCKET_SSL_INVALID_USER_DATA:
            return tr("ERROR_QSOCKET_SSL_INVALID_USER_DATA");
        case ERROR_QSOCKET_TEMPORARY:
            return tr("ERROR_QSOCKET_TEMPORARY");
        case ERROR_QSOCKET_UNKNOW:
            return tr("ERROR_QSOCKET_UNKNOW");
        case ERROR_QSOCKET_WRITE:
            return tr("ERROR_QSOCKET_WRITE");
        //tr:未知错误描述
        default:
            return tr("ERROR_UNKNOWN_DESCRIPTION");
    }
}
