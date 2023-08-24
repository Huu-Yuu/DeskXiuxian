#include "filedata/datamanage.h"

void DataManage::InitRemoteData()
{
    database_ = QSqlDatabase::addDatabase("QMYSQL");
    database_.setHostName(REMOTE_DB_ADDRESS);
    database_.setPort(REMOTE_DB_PORT);
    database_.setUserName(REMOTE_DB_USERNAME);
    database_.setPassword(REMOTE_DB_PASSWORD);
    database_.setDatabaseName(REMOTE_DB_NAME);

    if (database_.open())
    {
        qDebug() << "远程数据服务连接正常";
        // 连接成功后，可以执行其他初始化操作
        // ...
        database_.close(); // 关闭数据库连接
    }
    else
    {
        qDebug() << "远程数据服务连接失败";
        // 处理连接失败的情况
        // ...
    }
}

void DataManage::OpenDatabase(QString host, int port, QString username, QString password, QString databaseName)
{
    // 打开现有数据库连接
    database_ = QSqlDatabase::addDatabase("QMYSQL");
    database_.setHostName(host);
    database_.setPort(port);
    database_.setUserName(username);
    database_.setPassword(password);
    database_.setDatabaseName(databaseName);

    // 打开数据库连接
    if (!database_.open())
    {
        qDebug() << "无法打开数据库:" << database_.lastError().text();
    }
    else
    {
        qDebug() << "数据库已经打开.";
        if(!CheckTablesExist()) //检查并创建表单
        {
            qDebug() << "检查表单时出现错误";
            database_.close();
        }
    }
}
