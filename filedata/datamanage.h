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
#include <QJsonObject>

/**
 * @brief 文件管理类
 */
class DataManage : public QObject
{
public:

    /**
     * @brief 获取单例
     */
    static DataManage* GetInstance();

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


    ~DataManage();

public slots:

    /**
     * @brief 保存角色基本信息槽函数
     */
    void SlotSaveRoleInfoToDatabase(QJsonObject role_data);

private:
    DataManage();
    // 阻止拷贝构造函数和赋值运算符
    DataManage(const DataManage&) = delete;
    DataManage& operator=(const DataManage&) = delete;
    static QMutex mutex;  // 互斥锁
    static DataManage* instance;  // 单例对象指针

    void OpenDatabase(QString path);
    void CreateDatabase(QString path);
    bool CheckTablesExist();

    /**
     * @brief 配置文件读取
     */
    QSettings *file_setting_;

    /**
     * @brief 数据库操作
     */
    QSqlDatabase database_;

};

#endif // DATAMANAGE_H
