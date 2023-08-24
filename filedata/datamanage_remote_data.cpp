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

bool DataManage::LoginVerification(QString user_name, QString pass_word)
{
    if (!database_.open()) {
        qDebug() << "无法连接到数据库";
        return false;
    }

    // 执行查询语句
    QSqlQuery query;
    query.prepare("SELECT * FROM UserDataInfo WHERE UserName = :userName AND PassWord = :password");
    query.bindValue(":userName", user_name);
    query.bindValue(":password", pass_word);

    if (!query.exec())
    {
        qDebug() << "校验失败：" << query.lastError().text();
        database_.close();
        return false;
    }

    if (query.next())
    {
        qDebug() << "校验成功";
        database_.close();
        return true;
    } else
    {
        qDebug() << "用户名或密码错误";
        database_.close();
        return false;
    }
}

bool DataManage::AccountRegistration(QString user_name, QString pass_word)
{
    if (!database_.open())
    {
        qDebug() << "无法连接到数据库";
        return false;
    }

    // 检查用户名是否已存在
    QSqlQuery existQuery;
    existQuery.prepare("SELECT UserName FROM UserDataInfo WHERE UserName = :userName");
    existQuery.bindValue(":userName", user_name);

    if (!existQuery.exec()) {
        qDebug() << "查询失败：" << existQuery.lastError().text();
        database_.close();
        return false;
    }

    if (existQuery.next()) {
        qDebug() << "用户名已存在";
        database_.close();
        return false;
    }

    // 执行插入语句
    QString uuid = QUuid::createUuid().toString();
    QString reg_time = QDate::currentDate().toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery query;
    query.prepare("INSERT INTO UserDataInfo (UUID, UserName, PassWord, RegistrationTime) VALUES (:uuid, :userName, :password, :registrationTime)");
    query.bindValue(":uuid", uuid);
    query.bindValue(":userName", user_name);
    query.bindValue(":password", pass_word);
    query.bindValue(":registrationTime", reg_time);

    if (!query.exec()) {
        qDebug() << "注册失败：" << query.lastError().text();
        database_.close();
        return false;
    }

    qDebug() << "注册成功";
    user_UUID_ = uuid;
    database_.close();
    return true;
}

bool DataManage::AutomaticLogin()
{
    // 先获取本地保存的账号密码
    QString user_name = GetSettingUserName();
    QString pass_word = GetSettingPassWord();
    if(user_name == "" || pass_word == "")
    {
        qDebug() << "账号密码不存在，跳过自动登录";
        return false;
    }
    if(!LoginVerification(user_name, pass_word))
    {
        qDebug() << "账号校验不通过，跳过自动登录";
        return false;
    }
    user_UUID_ = GetTableToInfo("UserDataInfo","UUID");
    qDebug() << "账号校验成功，获取UUID";
    return true;;
}
