#include "datamanage.h"

DataManage::DataManage()
{
    file_setting_.setPath(QSettings::IniFormat, QSettings::UserScope,
                          QCoreApplication::applicationDirPath() + "/config.ini");
    file_setting_.setIniCodec("UTF-8");

    // 获取数据库文件路径
    QString databasePath = QCoreApplication::applicationDirPath() + "/database.db";

    // 检查数据库文件是否存在
    QFileInfo databaseFile(databasePath);
    if (!databaseFile.exists())
    {
        // 数据库文件不存在，创建新的数据库
        CreateDatabase(databasePath);
    }
    else
    {
        // 数据库文件已存在，读取现有数据库
        OpenDatabase(databasePath);
    }
}

void DataManage::OpenDatabase(QString path)
{
    // 打开现有数据库连接
    database_ = QSqlDatabase::addDatabase("QSQLITE");
    database_.setDatabaseName(path);

    // 打开数据库连接
    if (!database_.open())
    {
        qDebug() << "无法打开数据库:" << database_.lastError().text();
    }
    else
    {
        qDebug() << "数据库已经打开.";
    }
}

void DataManage::CreateDatabase(QString path)
{
    // 创建数据库连接
    database_ = QSqlDatabase::addDatabase("QSQLITE");
    database_.setDatabaseName(path);

    // 打开数据库连接
    if (!database_.open())
    {
        qDebug() << "Failed to create database:" << database_.lastError().text();
    }
    else
    {
        qDebug() << "Database created.";
    }

    // 在此处可以执行数据库表的初始化操作
    // ...
}
