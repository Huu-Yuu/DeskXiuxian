#include "datamanage.h"

DataManage::DataManage()
{
    QString configFilePath = QCoreApplication::applicationDirPath() + "/config.ini";

    // 检查配置文件是否存在
    QFileInfo configFile(configFilePath);
    if (!configFile.exists())
    {
        // 配置文件不存在，创建一个空文件
        QFile file(configFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.close();
        }
        else
        {
            // 文件创建失败，进行错误处理
            // ...
            qDebug() << "配置文件创建失败";
        }
    }
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

QString DataManage::GetRoleName()
{
    return file_setting_.value("RoleName").toString();
}

QString DataManage::GetLastGameTime()
{
    return file_setting_.value("Date").toString();
}
