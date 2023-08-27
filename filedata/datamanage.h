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
    QString GetTableToInfo(const QString table_name, const QString column_name,const QString leach_column, QString leach_value);

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
     * @return 1-登录成功 0-账号或密码错误 -1-数据库连接失败
     */
    int LoginVerification(const QString user_name, const QString pass_word);

    /**
     * @brief 账号注册
     * @return 1-注册成功 0-注册失败 -2-数据库连接失败 -1-账号已存在
     */
    int AccountRegistration(const QString user_name, const QString pass_word, const QString email);

    /**
     * @brief 检查角色昵称是否可用
     */
    bool CheckRoleNameIsOk(const QString role_name);

    /**
     * @brief 修改角色名
     * @return 1-修改成功 0-修改失败 -1-数据库操作失败
     */
    int ModifyRoleName(const QString new_name);

    /**
     * @brief 自动登录
     */
    bool AutomaticLogin();

    /**
     * @brief 获取用户UUID
     */
    QString GetUserUUID(const QString user_name,const QString pass_word);

    /**
     * @brief 检查用户是否首次登录
     * @return 1-首次登录 0-非首次登录 -1-数据库查询失败
     */
    int CheckUserLogginIsFist();

    /**
     * @brief 初始化角色信息
     */
    int InitRoleData();

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
     * @return 1-写入正常 0-更新失败 -1-更新查询失败 -2-不存在这一行 -3-计数查询失败
     */
    int WriteRoleInfoToRemoteDatabase();

    /**
     * @brief 写入角色物品信息到     远程数据库
     * @return 1-写入正常 0-更新失败 -1-更新查询失败 -2-不存在这一行 -3-计数查询失败
     */
    int WriteRoleItemsToRemoteDatabase();

    /**
     * @brief 写入角色计算系数信息到   远程数据库
     * @return 1-写入正常 0-更新失败 -1-更新查询失败 -2-不存在这一行 -3-计数查询失败
     */
    int WriteRoleCoefficientToRemoteDatabase();

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
     * @brief 数据库链接
     */
    QSqlDatabase database_;

//    /**
//     * @brief 数据库查询语句
//     */
//    QSqlQuery* sql_query_;

    bool is_SaveRoleInfo = false;           // 保存角色信息开关
    bool is_SaveRoleItem = false;           // 保存角色物品开关
    bool is_SaveRoleCoefficient = false;    // 保存角色系数开关
    bool is_GetDataBaseInfo = false;        // 获取数据库信息开关
    bool is_FirstCreation = false;          // 是否首次创建，用于命名角色

    QJsonObject role_data;      // 角色基本数据
    QJsonObject role_item_data; // 角色物品数据
    QJsonObject RC_data;        // 角色系数

    static QString user_uuid_ ;          // 账号UUID

};

#endif // DATAMANAGE_H
