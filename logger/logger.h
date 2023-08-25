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
#include "public/error_code.h"

/**
 * @brief 日志记录器
 */
class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger* GetInstance();

    ~Logger();

    /**
     * @brief 获取错误码基类型
     * @param error_code：错误码
     * @return 错误码位与ERROR_BASE_MASK部分
     */
    static int GetErrorBaseType(int error_code);

    /**
     * @brief 获取错误码基编号
     * @param error_code：错误码
     * @return 错误码位与ERROR_CODE_MASK部分
     */
    static int GetErrorBaseCode(int error_code);

    /**
     * @brief 程序信息重定向处理函数
     * @param type：Qt信息输出类型
     * @param context：相关信息
     * @param msg：输出信息内容
     * @return 无
     * @note 该函数使用qInstallMessageHandler()注册后，由系统在输入程序信息时调用。
     */
    static void OutputMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

    /**
     * @brief 获取错误类型函数
     * @param error_code：错误码
     * @return 错误类型
     * @note 错误类型为error_code.h中各类第一个xxx_BASE注释信息，修改在翻译文件中修改。
     */
    QString GetErrorTypeName(int error_type_base);

    /**
     * @brief 获取错误描述函数
     * @param error_code：错误码
     * @return 错误描述
     * @note 错误描述为error_code.h中错误码后方注释信息，修改在翻译文件中修改。
     */
    QString GetErrorDescription(int error_code);

signals:

public slots:
    /**
     * @brief 打印日志槽函数
     */
    void SlotOutTolog(QtMsgType type, const QMessageLogContext& context, const QString& message);

private:
    explicit Logger(QObject* parent = nullptr);
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    static Logger* instance;  // 单例对象指针
    QFile logFile_;
    QTextStream logStream_;
    QThread thread_;
    static QMutex mutex_; // 互斥锁，用于线程同步
    //调试信息输出锁
    static QMutex std_log_mutex;
};

#endif // LOGGER_H
