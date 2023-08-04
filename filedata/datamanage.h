#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFileInfo>
#include <QDebug>

/**
 * @brief 文件管理类
 */
class DataManage
{
public:
    DataManage();
    void init();

private:
    void OpenDatabase(QString path);
    void CreateDatabase(QString path);

    /**
     * @brief 配置文件读取
     */
    QSettings file_setting_;

    /**
     * @brief 数据库读取
     */
    QSqlDatabase database_;

};

#endif // DATAMANAGE_H
