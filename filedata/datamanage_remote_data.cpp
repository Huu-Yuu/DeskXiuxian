#include "filedata/datamanage.h"

void DataManage::InitRemoteData()
{
    database_ = QSqlDatabase::addDatabase("QMYSQL");
    database_.setHostName(REMOTE_DB_ADDRESS);
    database_.setPort(REMOTE_DB_PORT);
    database_.setUserName(REMOTE_DB_USERNAME);
    database_.setPassword(REMOTE_DB_PASSWORD);
    database_.setDatabaseName(REMOTE_DB_NAME);

    // 初始化数据库查询语句
    sql_query_ = QSqlQuery(database_);

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

int DataManage::LoginVerification(QString user_name, QString pass_word)
{
    int result = -1;
    if (!database_.open()) {
        qDebug() << "无法连接到数据库";
        return result;
    }

    // 执行查询语句
    sql_query_.finish();
    sql_query_.prepare("SELECT * FROM UserDataInfo WHERE UserName = :userName AND PassWord = :password");
    sql_query_.bindValue(":userName", user_name);
    sql_query_.bindValue(":password", pass_word);

    if (!sql_query_.exec())
    {
        qDebug() << "校验失败：" << sql_query_.lastError().text();
        database_.close();
        return result;
    }

    if (sql_query_.next())
    {
        qDebug() << "校验成功";
        user_UUID_ = GetUserUUID(user_name, pass_word);
        database_.close();
        result = 1;
    }
    else
    {
        qDebug() << "用户名或密码错误";
        database_.close();
        result = 0;
    }
    return result;
}

int DataManage::AccountRegistration(QString user_name, QString pass_word, QString email)
{
    if (!database_.open())
    {
        qDebug() << "无法连接到数据库";
        return -2;
    }

    // 检查用户名是否已存在
    sql_query_.finish();
    sql_query_.prepare("SELECT UserName FROM UserDataInfo WHERE UserName = :userName");
    sql_query_.bindValue(":userName", user_name);

    if (!sql_query_.exec()) {
        qDebug() << "查询失败：" << sql_query_.lastError().text();
        database_.close();
        return 0;
    }

    if (sql_query_.next()) {
        qDebug() << "用户名已存在";
        database_.close();
        return -1;
    }

    // 执行插入语句
    QString uuid = QUuid::createUuid().toString();
    QString reg_time = QDate::currentDate().toString("yyyy-MM-dd hh:mm:ss");
    QString role_name = user_name.right(4);
    QSqlQuery query(database_);
    query.prepare("INSERT INTO UserDataInfo (UUID, UserName, PassWord, EMail, RegistrationTime, RoleName, LastLoginTime) "
                  "VALUES (:UUID, :UserName, :PassWord,:EMail, :RegistrationTime, :RoleName, :LastLoginTime)");
    query.bindValue(":UUID", uuid);
    query.bindValue(":UserName", user_name);
    query.bindValue(":PassWord", pass_word);
    query.bindValue(":EMail", email);
    query.bindValue(":RegistrationTime", reg_time);
    query.bindValue(":RoleName", role_name);
    query.bindValue(":LastLoginTime", 0);

    if (!query.exec()) {
        qDebug() << "注册失败：" << query.lastError().text();
        database_.close();
        return 0;
    }

    qDebug() << "注册成功";
    //    user_UUID_ = uuid;
    database_.close();
    return 1;
}

bool DataManage::AutomaticLogin()
{
    bool result = false;
    // 先获取本地保存的账号密码
    QString user_name = GetSettingUserName();
    QString pass_word = GetSettingPassWord();
    if(user_name == "" || pass_word == "")
    {
        qDebug() << "账号密码不存在，跳过自动登录";
    }
    if(LoginVerification(user_name, pass_word) != 1)
    {
        qDebug() << "账号校验不通过，跳过自动登录";
    }
    user_UUID_ = GetUserUUID(user_name, pass_word);
    if(user_UUID_ != "")
    {
        qDebug() << "账号校验成功，获取UUID";
        result = true;
    }
    return result;;
}

bool DataManage::CheckRoleNameIsOk(const QString role_name)
{
    bool result = false;
    if (database_.open()) {
        sql_query_.finish();
        QString queryString = QString("SELECT RoleName FROM UserDataInfo WHERE RoleName = '%1'").arg(role_name);

        if (sql_query_.exec(queryString) && sql_query_.next()) {
            // 查询成功且有结果，表示存在
            result = false;
        }
        else
        {
            result = true;;
        }
    }
    database_.close();
    return result;
}

QString DataManage::GetUserUUID(const QString user_name,const QString pass_word)
{
    QString uuid = "";

    if(!database_.open())
    {
        return uuid;
    }
    // 准备查询语句
    QString queryString = "SELECT UUID FROM UserDataInfo WHERE UserName = :userName AND Password = :password";

    // 创建查询对象
    sql_query_.finish();
    sql_query_.prepare(queryString);
    sql_query_.bindValue(":userName", user_name);
    sql_query_.bindValue(":password", pass_word);

    // 执行查询
    if (sql_query_.exec() && sql_query_.next()) {
        // 获取查询结果
        uuid = sql_query_.value("UUID").toString();
        qDebug() <<"成功获取UUID：" << uuid;
    }
    else
    {
        qDebug() <<"获取UUID失败 返回空值";
    }
    database_.close();
    return uuid;
}

int DataManage::CheckUserLogginIsFist(const QString user_name,const QString pass_word)
{
    int result = -1;
    if(!database_.open())
    {
        return result;
    }
    QString last_time = "";
    QString queryString = "SELECT UUID FROM UserDataInfo WHERE UserName = :userName AND Password = :password";
    sql_query_.finish();
    sql_query_.prepare(queryString);
    sql_query_.bindValue(":userName", user_name);
    sql_query_.bindValue(":password", pass_word);

    // 执行查询
    if (sql_query_.exec() && sql_query_.next()) {
        // 获取查询结果
        last_time = sql_query_.value("LastLoginTime").toString();
        if(last_time == "0")
        {
            qDebug() << "检测到首次登录";
            result = 1;
        }
        else
        {
            qDebug() << "非首次登录";
            result = 0;
        }
    }
    else
    {
        qDebug() << "首次登录数据库查询失败";
    }
    database_.close();
    return result;
}

int DataManage::ModifyRoleName(const QString new_name)
{
    int result = -1;
    if(!database_.open())
    {
        return result;
    }
    QString queryString = "UPDATE UserDataInfo SET RoleName = :newName WHERE UUID = :uuid";

    // 创建查询对象
    sql_query_.finish();
    sql_query_.prepare(queryString);
    sql_query_.bindValue(":newName", new_name);
    sql_query_.bindValue(":uuid", user_UUID_);

    // 执行更新
    if (sql_query_.exec()) {
        // 检查受影响的行数
        if (sql_query_.numRowsAffected() > 0)
        {
            // 更新成功
            result = 1;
        }
        else
        {
            // UUID 不存在或角色名没有改变
            result = 0;
        }
    }
    database_.close();
    return result;
}

int DataManage::InitRoleData()
{
    int result = -1;
    if(!database_.open())
    {
        return result;
    }
    QString role_name = GetTableToInfo(user_UUID_, "UserDataInfo", "RoleName");
    if (role_name.isEmpty()) {
        // 查询角色名失败
        return result;
    }

    sql_query_.finish();
    sql_query_.prepare("INSERT INTO UserRoleInfo (ID, UUID, RoleName, RoleLife, RolePrestige, RoleAptitude, RoleExp,"
                       " RoleAgg, RoleDef, RoleHP, RoleCurExp, RoleLV,"
                       " EquipWeapon, EquipMagic, EquipHelmet, EquipClothing, EquipBritches, EquipShoe, EquipJewelry, EquipMount,"
                       " RCLife, RCBasicEvent, RCAttEvent, RCSurviveDisaster, RCPrestigeEvent, RCSpecialEvent) "
                  "VALUES (:id, :uuid, :roleName, 20, 0, 0, 0, 20, 10, 100, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");

    // 获取 UserRoleInfo 表的总行数
    QString countQuery = "SELECT COUNT(*) FROM UserRoleInfo";
    QSqlQuery countQueryObj(database_);
    if (countQueryObj.exec(countQuery) && countQueryObj.next()) {
        int rowCount = countQueryObj.value(0).toInt();
        sql_query_.bindValue(":id", rowCount + 1);
    }
    else
    {
        // 获取总行数失败
        return result;
    }

    sql_query_.bindValue(":uuid", user_UUID_);
    sql_query_.bindValue(":roleName", role_name);

    if (sql_query_.exec())
    {
        result = 1;  // 插入成功
    }
    else
    {
        result = -1; // 数据库操作错误
    }

    return result;
}

QString DataManage::GetTableToInfo(const QString leach_name, QString table_name, QString column_name)
{
    QString result;
    if(!database_.open())
    {
        return result;
    }
    // 准备查询语句
    QString queryString = QString("SELECT %1 FROM %2 WHERE %3 = :leach").arg(column_name, table_name, leach_name);

    // 创建查询对象
    sql_query_.finish();
    sql_query_.prepare(queryString);
    sql_query_.bindValue(":leach", leach_name);

    // 执行查询
    if (sql_query_.exec() && sql_query_.next()) {
        // 获取查询结果
        result = sql_query_.value(column_name).toString();
    }
    database_.close();
    return result;
}
