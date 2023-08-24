#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFileInfo>
#include <QDebug>
#include <QDate>
#include <QSqlQuery>
#include <QMutex>
#include <QThread>
#include <QJsonObject>
#include <QUuid>
#include "public/public_macro.h"
#include "logger/logger.h"

/**
 * @brief 文件管理类
 */
class DataManage : public QThread
{
public:

    /**
     * @brief 获取单例
     */
    static DataManage* GetInstance();

    /**
     * @brief 初始化配置文件
     */
    void InitSettingFile();

    /**
     * @brief 初始化远程数据库
     */
    void InitRemoteData();

    /**
     * @brief 获取表单中对应的列数据
     * @return 查询不到则返回空，否则返回查询值
     */
    QString GetTableToInfo(QString table_name, QString column_name);

    /**
     * @brief 获取上次游戏时间
     */
    QString GetLastGameTime();

    /**
     * @brief 关闭数据库
     */
    void DatabaseClose();

    /**
     * @brief 写入游戏配置，最后登录时间、用户信息
     */
    void SetGameConfigInfo(QString user_name = nullptr, QString pass_word = nullptr);

    /**
     * @brief 登录校验
     */
    bool LoginVerification(QString user_name, QString pass_word);

    /**
     * @brief 账号注册
     */
    bool AccountRegistration(QString user_name, QString pass_word);

    /**
     * @brief 自动登录
     */
    bool AutomaticLogin();

//    /**
//     * @brief 获取用户UUID
//     */
//    bool GetUserUUID();

    void run();

    ~DataManage();

    /**
     * @brief 打印日志
     */
    void DebugOutToLog(QString msg);

signals:
    /**
     * @brief 发送日志输出信号
     */
    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);

public slots:

    /**
     * @brief 保存角色基本信息数据 槽函数
     */
    void SlotSaveRoleInfoToDatabase(QJsonObject role_data);

    /**
     * @brief 保存角色物品数据 槽函数
     */
    void SlotSaveRoleItemToDatabase(QJsonObject role_item_data);

    /**
     * @brief 保存角色相关属性系数数据 槽函数
     */
    void SlotSaveRoleCoefficientToDatabase(QJsonObject RC_data);

private:
    DataManage();
    // 阻止拷贝构造函数和赋值运算符
    DataManage(const DataManage&) = delete;
    DataManage& operator=(const DataManage&) = delete;
    static QMutex mutex;  // 互斥锁
    static DataManage* instance;  // 单例对象指针

    /**
     * @brief 打开数据库
     */
    void OpenDatabase(QString path);

    /**
     * @brief 创建数据库
     */
    void CreateDatabase(QString path);

    /**
     * @brief 检查数据库
     */
    bool CheckTablesExist();

    /**
     * @brief 写入角色基本信息到     远程数据库
     */
    void WriteRoleInfoToRemoteDatabase();

    /**
     * @brief 写入角色物品信息到     远程数据库
     */
    void WriteRoleItemsToRemoteDatabase();

    /**
     * @brief 写入角色计算系数信息到   远程数据库
     */
    void WriteRoleCoefficientToRemoteDatabase();

    /**
     * @brief 写入角色物品信息到     本地数据库
     */
    void WriteRoleItemsToLocalDatabase();

    /**
     * @brief 写入角色计算系数信息到   本地数据库
     */
    void WriteRoleCoefficientToLocalDatabase();

    /**
     * @brief 写入角色基本信息到     本地数据库
     */
    void WriteRoleInfoToLocalDatabase();

    /**
     * @brief 获取本地保存的账号
     */
    QString GetSettingUserName();

    /**
     * @brief 获取本地保存的密码
     */
    QString GetSettingPassWord();

    /**
     * @brief 配置文件读取
     */
    QSettings* file_setting_;

    /**
     * @brief 数据库操作
     */
    QSqlDatabase database_;

    bool is_SaveRoleInfo = false;
    bool is_SaveRoleItem = false;
    bool is_SaveRoleCoefficient = false;
    bool is_GetDataBaseInfo = false;

    QJsonObject role_data;      // 角色基本数据
    QJsonObject role_item_data; // 角色物品数据
    QJsonObject RC_data;        // 角色系数

    QString user_UUID_;          // 账号UUID

};

#endif // DATAMANAGE_H
