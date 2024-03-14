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
#include "modules/public/public_macro.h"
#include "modules/public/public_func.h"
#include "modules/logger/logger.h"
#include "common/singleton.h"

/**
 * @brief 文件管理类
 */
class DataManage : public QThread
{

public:
    SINGLETON(DataManage);
    DataManage();

    void InitSettingFile(); ///< 初始化配置文件
    void InitRemoteData();  ///< 初始化远程数据库
    void InitLocalData();   ///< 初始化本地数据库

    /**
     * @brief 获取表单中对应的列数据
     * @return 查询不到则返回空，否则返回查询值
     */
    QString GetTableToInfo(QString table_name, QString column_name);
    QString GetTableToInfo(const QString table_name, const QString column_name, const QString leach_column, QString leach_value);

    /**
     * @brief 写入表单中对应的列数据
     * @return 1-写入成功 非1-写入错误
     */
    int SetTableToInfo(const QString table_name, const QString column_name, const QString leach_column,
                       QString leach_value, QString new_value);
    QString GetLastGameTime();  ///< 获取上次游戏时间
    void DatabaseClose();   ///< 关闭数据库
    void SetGameConfigInfo();   ///< 写入游戏配置，最后登录时间
    void SetUserInfoToConfig(QString user_name, QString pass_word, QString email);  ///< 写入用户信息到配置文件

    /**
     * @brief 登录校验
     * @return 1-登录成功 0-账号或密码错误 -1-数据库连接失败
     */
    int LoginVerification(const QString& user_name, const QString& pass_word);

    /**
     * @brief 账号注册
     * @return 1-注册成功 0-注册失败 -2-数据库连接失败 -1-账号已存在
     */
    int AccountRegistration(const QString user_name, const QString pass_word, const QString email);

    bool CheckRoleNameIsOk(const QString role_name);    ///< 检查角色昵称是否可用

    /**
     * @brief 修改角色名
     * @return 1-修改成功 0-修改失败 -1-数据库操作失败
     */
    int ModifyRoleName(const QString new_name);
    bool AutomaticLogin();  ///< 自动登录
    QString GetUserUUID(const QString user_name, const QString pass_word);  ///< 获取用户UUID

    /**
     * @brief 检查用户是否首次登录
     * @return 1-首次登录 0-非首次登录 -1-数据库查询失败
     */
    int CheckUserLogginIsFist();

    /**
     * @brief 初始化角色信息
     * @return 1-初始化成功 非1-初始化失败
     */
    int InitRoleData();
    int InitRoleRemoteData();       // 暂时没使用


    /**
     * @brief 获取远程数据库 角色信息
     * @return 1-获取成功 非1-获取失败
     */
    QJsonObject GetRemoteRoleInfo();

    /**
     * @brief 获取远程数据库 角色装备
     * @return 1-获取成功 非1-获取失败
     */
    QJsonObject GetRemoteRoleEquip();

    /**
     * @brief 获取远程数据库 角色物品
     * @return 1-获取成功 非1-获取失败
     */
    QJsonObject GetRemoteRoleItem();

    /**
     * @brief 获取远程数据库 角色成长系数
     * @return 1-获取成功 非1-获取失败
     */
    QJsonObject GetRemoteRoleRC();

    void run();

    ~DataManage();

    /**
     * @brief 打印日志
     */
    void DebugOutToLog(QString msg);

public slots:

    void SlotSaveRoleInfoToDatabase(const QJsonObject& role_data); ///< 保存角色基本信息数据 槽函数
    void SlotSaveRoleItemToDatabase(const QJsonObject& role_item_data);    ///< 保存角色物品数据 槽函数
    void SlotSaveRoleEquipToDatabase(const QJsonObject& role_equip_data);    ///< 保存角色物品数据 槽函数
    void SlotSaveRoleCoefficientToDatabase(const QJsonObject& RC_data);    ///< 保存角色相关属性系数数据 槽函数
    void SlotUpdataLoginLog();  ///< 更新登录日志 槽函数
private:
    static QMutex mutex;  // 互斥锁

    void OpenDatabase(QString path);    ///< 打开数据库
    void CreateDatabase(QString path);  ///< 创建数据库
    bool CheckTablesExist();    ///< 检查数据库

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
     * @brief 写入账号登录日志到   远程数据库
     * @return 1-写入正常 0-更新失败 -1-更新查询失败 -2-不存在这一行 -3-计数查询失败
     */
    int WriteUserLoginLogToRemoteDatabase();
    void WriteRoleItemsToLocalDatabase();   ///< 写入角色物品信息到     本地数据库
    void WriteRoleEquipToLocalDatabase();   ///< 写入角色装备信息到     本地数据库
    void WriteRoleCoefficientToLocalDatabase(); ///< 写入角色计算系数信息到   本地数据库
    void WriteRoleInfoToLocalDatabase();    ///< 写入角色基本信息到     本地数据库
    QString GetSettingUserName();   ///< 获取本地保存的账号
    QString GetSettingPassWord();   ///< 获取本地保存的密码

    /**
     * @brief 角色是否已经初始化
     * @return 1-是 非1-否或遇到错误
     */
    int IsRoleDataInited();

    static QSettings* file_setting_;    ///< 配置文件读取

    QSqlDatabase m_database_;     ///< 数据库链接


    bool is_SaveRoleInfo = false;           ///< 保存角色信息开关
    bool is_SaveRoleItem = false;           ///< 保存角色物品开关
    bool is_SaveRoleEquip = false;           ///< 保存角色物品开关
    bool is_SaveRoleCoefficient = false;    ///< 保存角色系数开关
    bool is_FirstCreation = false;          ///< 是否首次创建，用于命名角色
    bool is_SaveLoginLog = false;           ///< 上传登录日志开关 登录时间 IP UUID 角色名 等级

    QJsonObject role_data_;      ///< 角色基本数据
    QJsonObject role_item_data_; ///< 角色物品数据
    QJsonObject role_equip_data_; ///< 角色物品数据
    QJsonObject RC_data_;        ///< 角色系数

    static QString user_uuid_ ;          ///< 账号UUID
    static QString user_ip_ ;      ///< 用户IP

};

#endif // DATAMANAGE_H
