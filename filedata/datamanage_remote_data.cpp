#include "filedata/datamanage.h"

void DataManage::InitRemoteData()
{
    QSqlDatabase database_;
    database_ = QSqlDatabase::addDatabase("QMYSQL", REMOTE_DB_LINKNAME);
    database_.setHostName(REMOTE_DB_ADDRESS);
    database_.setPort(REMOTE_DB_PORT);
    database_.setUserName(REMOTE_DB_USERNAME);
    database_.setPassword(REMOTE_DB_PASSWORD);
    database_.setDatabaseName(REMOTE_DB_NAME);
    // 初始化数据库查询语句
    if (database_.open())
    {
        qDebug() << "远程数据服务连接正常";
        // 连接成功后，可以执行其他初始化操作
        // ...
        // database_.close(); // 关闭数据库连接
    }
    else
    {
        qDebug() << "远程数据服务连接失败";
        // 处理连接失败的情况
        // ...
    }
    user_ip_ = PublicFunc::GetLocalIpAddress();
    qDebug() << "获取到当前IP地址为：" << user_ip_;
}

int DataManage::LoginVerification(QString user_name, QString pass_word)
{
    int result = -1;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);

    // 执行查询语句
    query.prepare("SELECT * FROM user_data_info WHERE user_name = :userName AND pass_word = :password");
    query.bindValue(":userName", user_name);
    query.bindValue(":password", pass_word);

    if (!query.exec())
    {
        qDebug() << "校验失败：" << query.lastError().text();
        return result;
    }

    if (query.next())
    {
        qDebug() << "校验成功";
        user_uuid_ = GetUserUUID(user_name, pass_word);
        if(CheckUserLogginIsFist() == 1)
        {
            if(InitRoleData() == 1)
            {
                result = 1;
            }
        }
    }
    else
    {
        qDebug() << "用户名或密码错误";
        result = 0;
    }
    return result;
}

int DataManage::AccountRegistration(QString user_name, QString pass_word, QString email)
{
    int result = -2;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    // 检查用户名是否已存在
    query.prepare("SELECT user_name FROM user_data_info WHERE user_name = :userName");
    query.bindValue(":userName", user_name);

    if (!query.exec())
    {
        qDebug() << "查询失败：" << query.lastError().text();
        return 0;
    }

    if (query.next())
    {
        qDebug() << "用户名已存在";
        return -1;
    }

    // 执行插入语句
    QString uuid = QUuid::createUuid().toString();
    QDate reg_time = QDate::currentDate();
    QString role_name = user_name.right(4);
    QString countQuery = "SELECT COUNT(*) FROM user_role_info";
    query.prepare(countQuery);
    if (query.exec() && query.next())
    {
        int rowCount = query.value(0).toInt();
        query.prepare("INSERT INTO user_data_info (id, uuid, user_name, pass_word, email, "
                      "registration_time, role_name, last_login_time, level, ip) "
                      "VALUES (:id, :UUID, :UserName, :PassWord,:EMail, :RegistrationTime, :RoleName, :LastLoginTime, :Level, :Ip)");
        query.bindValue(":UUID", uuid);
        query.bindValue(":UserName", user_name);
        query.bindValue(":PassWord", pass_word);
        query.bindValue(":EMail", email);
        query.bindValue(":RegistrationTime", reg_time);
        query.bindValue(":RoleName", role_name);
        query.bindValue(":LastLoginTime", reg_time);
        query.bindValue(":Level", 1);
        query.bindValue(":id", rowCount + 1);
        query.bindValue(":Ip", user_ip_);
        if (query.exec())
        {
            result = 1;  // 插入成功
        }
        else
        {
            result = -1; // 数据库操作错误
        }
    }
    else
    {
        // 获取总行数失败
        qDebug() << "获取总行数失败";
    }
    return result;
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
    if(LoginVerification(user_name, pass_word) == 1)
    {
        user_uuid_ = GetUserUUID(user_name, pass_word);
    }
    else
    {
        qDebug() << "账号校验不通过，跳过自动登录";
    }
    if(user_uuid_ != "")
    {
        qDebug() << "账号校验成功，获取UUID";
        result = true;
    }
    return result;;
}

bool DataManage::CheckRoleNameIsOk(const QString role_name)
{
    bool result = false;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    QString queryString = QString("SELECT RoleName FROM user_data_info WHERE RoleName = '%1'").arg(role_name);

    if (query.exec(queryString) && query.next())
    {
        // 查询成功且有结果，表示存在
        result = false;
    }
    else
    {
        result = true;
    }
    return result;
}

QString DataManage::GetUserUUID(const QString user_name, const QString pass_word)
{
    QString uuid = "";
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    // 准备查询语句
    QString queryString = "SELECT uuid FROM user_data_info WHERE user_name = :userName AND pass_word = :password";
    query.prepare(queryString);
    query.bindValue(":userName", user_name);
    query.bindValue(":password", pass_word);

    // 执行查询
    if (query.exec() && query.next())
    {
        // 获取查询结果
        uuid = query.value("UUID").toString();
        qDebug() << "成功获取UUID：" << uuid;
    }
    else
    {
        qDebug() << "获取UUID失败 返回空值";
    }
    return uuid;
}

int DataManage::CheckUserLogginIsFist()
{
    int result = -1;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    QString last_time = "0";
    QString reg_time = "1";
    QString queryString = "SELECT registration_time, last_login_time FROM user_data_info WHERE uuid = :uuid";

    query.prepare(queryString);
    query.bindValue(":uuid", user_uuid_);

    // 执行查询
    if (query.exec() && query.next())
    {
        // 获取查询结果
        reg_time = query.value("registration_time").toString();
        last_time = query.value("last_login_time").toString();
        if(last_time == reg_time)
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
    return result;
}

int DataManage::ModifyRoleName(const QString new_name)
{
    int result = -3;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM user_role_info WHERE uuid = :UUID");
    query.bindValue(":UUID", user_uuid_);

    if (query.exec() && query.next())
    {
        int rowCount = query.value(0).toInt();
        if (rowCount == 1)
        {
            QString queryString = "UPDATE user_data_info SET role_name = :newName WHERE uuid = :uuid";
            // 创建查询对象
            query.prepare(queryString);
            query.bindValue(":newName", new_name);
            qDebug() << user_uuid_;
            query.bindValue(":uuid", user_uuid_);

            if (query.exec())
            {
                // 检查受影响的行数
                if (query.numRowsAffected() > 0)
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
        }
        else
        {
            // 行数不为1，报错
            qDebug() << "查询错误：" << rowCount << "不存在这一行：" << user_uuid_;
            result = -2;
        }
    }
    else
    {
        // 查询执行失败，输出错误信息
        qDebug() << "计数查询失败:" << query.lastError().text();
    }
    return result;
}

int DataManage::InitRoleData()
{
    if(IsRoleDataInited() == 1)
    {
        qDebug() << "检测到角色已经初始化，将跳过本次初始化";
        return 1;
    }
    int result = -1;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    QString role_name = GetTableToInfo("user_data_info", "role_name", "UUID", user_uuid_);
    if (role_name.isEmpty())
    {
        // 查询角色名失败
        return result;
    }
    query.prepare("INSERT INTO user_role_info (uuid, role_name, role_life, role_prestige, role_aptitude, role_exp,"
                  " role_agg, role_def, role_hp, role_cur_exp, role_lv) "
                  "VALUES (:uuid, :roleName, 20, 0, 0, 0, 20, 10, 100, 0, 1)");
    query.bindValue(":uuid", user_uuid_);
    query.bindValue(":roleName", role_name);
    if (query.exec())
    {
        qDebug() << "新建角色基本信息初始化完成";
        result = 1;  // 插入成功
    }
    else
    {
        qDebug() << "插入操作失败，错误码：" << query.lastError().text();
        qDebug() << "新建角色基本信息初始化失败：" << query.lastError().text();
        result = -1;
    }
    query.prepare("INSERT INTO user_role_equip (uuid, equip_weapon, equip_magic, equip_helmet,"
                  " equip_clothing, equip_britches, equip_shoe, equip_jewelry, equip_mount) "
                  "VALUES (:uuid, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.bindValue(":uuid", user_uuid_);
    if (query.exec())
    {
        qDebug() << "新建角色装备信息初始化完成";
        result = 1;  // 插入成功
    }
    else
    {
        qDebug() << "插入操作失败，错误码：" << query.lastError().text();
        qDebug() << "新建角色装备信息初始化失败：" << query.lastError().text();
        result = -1;
    }
    query.prepare("INSERT INTO user_role_rc (uuid, rc_life, rc_basic_event, rc_att_event,"
                  " rc_survive_disaster, rc_prestige_event, rc_special_event) "
                  "VALUES (:uuid, 0, 0, 0, 0, 0, 0)");
    query.bindValue(":uuid", user_uuid_);
    if (query.exec())
    {
        qDebug() << "新建角色成长系数初始化完成";
        result = 1;  // 插入成功
    }
    else
    {
        qDebug() << "插入操作失败，错误码：" << query.lastError().text();
        qDebug() << "新建角色成长系数初始化失败：" << query.lastError().text();
        result = -1;
    }
    query.prepare("INSERT INTO user_role_item (uuid, role_money, rename_card) "
                  "VALUES (:uuid, 100, 1)");
    query.bindValue(":uuid", user_uuid_);
    if (query.exec())
    {
        qDebug() << "新建角色物品初始化完成";
        result = 1;  // 插入成功
    }
    else
    {
        qDebug() << "插入操作失败，错误码：" << query.lastError().text();
        qDebug() << "新建角色物品初始化失败：" << query.lastError().text();
        result = -1;
    }
    return result;
}

QString DataManage::GetTableToInfo(const QString table_name, const QString column_name,
                                   const QString leach_column, QString leach_value)
{
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    QString result;
    // 准备查询语句
    QString queryString = QString("SELECT %1 FROM %2 WHERE %3 = :leach").arg(column_name, table_name, leach_column);

    // 创建查询对象
    query.prepare(queryString);
    query.bindValue(":leach", leach_value);
    // 执行查询
    if (query.exec() && query.next())
    {
        // 获取查询结果
        result = query.value(column_name).toString();
    }
    return result;
}

int DataManage::WriteRoleInfoToRemoteDatabase()
{
    int result = -3;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM user_role_info WHERE uuid = :UUID");
    query.bindValue(":UUID", user_uuid_);

    if (query.exec() && query.next())
    {
        int rowCount = query.value(0).toInt();
        if (rowCount == 1)
        {
            // 执行更新操作
            QString updateQuery = "UPDATE user_role_info SET "
                                  "role_name = :roleName, "
                                  "role_life = :roleLife, "
                                  "role_prestige = :rolePrestige, "
                                  "role_lv = :roleLv, "
                                  "role_exp = :roleExp, "
                                  "role_agg = :roleAgg, "
                                  "role_def = :roleDef, "
                                  "role_hp = :roleHp, "
                                  "role_cur_exp = :roleCurExp "
                                  "WHERE uuid = :userUUID";
            query.prepare(updateQuery);
            query.bindValue(":roleName", role_data.value("roleName").toString());
            query.bindValue(":roleLife", role_data.value("roleLife").toInt());
            query.bindValue(":rolePrestige", role_data.value("rolePrestige").toInt());
            query.bindValue(":roleLv", role_data.value("roleLv").toInt());
            query.bindValue(":roleExp", role_data.value("roleExp").toInt());
            query.bindValue(":roleAgg", role_data.value("roleAgg").toInt());
            query.bindValue(":roleDef", role_data.value("roleDef").toInt());
            query.bindValue(":roleHp", role_data.value("roleHp").toInt());
            query.bindValue(":roleCurExp", role_data.value("roleCurExp").toInt());
            query.bindValue(":userUUID", user_uuid_);
            if (query.exec())
            {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected == 1)
                {
                    // 成功更新了一行数据
                    result = 1;
                }
                else
                {
                    // 更新行数不为1，可能出现多行或一行都没有的情况
                    result = 0;
                }
            }
            else
            {
                // 更新查询执行失败，输出错误信息
                qDebug() << "Update query failed:" << query.lastError().text();
                result = -1;
            }
        }
        else
        {
            // 行数不为1，报错
            qDebug() << "查询错误：" << rowCount << "不存在这一行：" << user_uuid_;
            result = -2;
        }
    }
    else
    {
        // 查询执行失败，输出错误信息
        qDebug() << "计数查询失败:" << query.lastError().text();
    }
    return result;
}

int DataManage::WriteRoleItemsToRemoteDatabase()
{
    int result = -3;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM user_role_item WHERE uuid = :UUID");
    query.bindValue(":UUID", user_uuid_);

    if (query.exec() && query.next())
    {
        int rowCount = query.value(0).toInt();
        if (rowCount == 1)
        {
            // 执行更新操作
            QString updateQuery = "UPDATE user_role_item SET "
                                  "role_money = :RoleMoney, "
                                  "rename_card = :ReNameCard "
                                  "WHERE uuid = :userUUID";
            query.prepare(updateQuery);
            query.bindValue(":RoleMoney", role_item_data.value("roleMoney").toString());
            query.bindValue(":ReNameCard", role_item_data.value("renameCard").toInt());
            query.bindValue(":userUUID", user_uuid_);
            if (query.exec())
            {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected == 1)
                {
                    // 成功更新了一行数据
                    result = 1;
                }
                else
                {
                    // 更新行数不为1，可能出现多行或一行都没有的情况
                    result = 0;
                }
            }
            else
            {
                // 更新查询执行失败，输出错误信息
                qDebug() << "Update query failed:" << query.lastError().text();
                result = -1;
            }
        }
        else
        {
            // 行数不为1，报错
            qDebug() << "查询错误：" << rowCount << "不存在这一行：" << user_uuid_;
            result = -2;
        }
    }
    else
    {
        // 查询执行失败，输出错误信息
        qDebug() << "计数查询失败:" << query.lastError().text();
    }
    return result;
}

int DataManage::WriteRoleCoefficientToRemoteDatabase()
{
    int result = -3;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM user_role_info WHERE uuid = :UUID");
    query.bindValue(":UUID", user_uuid_);

    if (query.exec() && query.next())
    {
        int rowCount = query.value(0).toInt();
        if (rowCount == 1)
        {
            // 执行更新操作
            QString updateQuery = "UPDATE user_role_info SET "
                                  "rc_life = :RCLife, "
                                  "rc_basic_event = :RCBasicEvent, "
                                  "rc_att_event = :RCAttEvent, "
                                  "rc_survive_disaster = :RCSurviveDisaster, "
                                  "rc_prestige_event = :RCPrestigeEvent, "
                                  "rc_special_event = :RCSpecialEvent, "
                                  "role_aptitude = :RoleAptitude "
                                  "WHERE uuid = :UUID";
            query.prepare(updateQuery);
            query.bindValue(":RCLife", RC_data.value("RCLife").toInt());
            query.bindValue(":RCBasicEvent", RC_data.value("RCBasicEvent").toInt());
            query.bindValue(":RCAttEvent", RC_data.value("RCAttEvent").toInt());
            query.bindValue(":RCSurviveDisaster", RC_data.value("RCSurviveDisaster").toInt());
            query.bindValue(":RCPrestigeEvent", RC_data.value("RCPrestigeEvent").toInt());
            query.bindValue(":RCSpecialEvent", RC_data.value("RCSpecialEvent").toInt());
            query.bindValue(":RoleAptitude", RC_data.value("roleAptitude").toInt());
            query.bindValue(":UUID", user_uuid_);
            if (query.exec())
            {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected == 1)
                {
                    // 成功更新了一行数据
                    result = 1;
                }
                else
                {
                    // 更新行数不为1，可能出现多行或一行都没有的情况
                    result = 0;
                }
            }
            else
            {
                // 更新查询执行失败，输出错误信息
                qDebug() << "Update query failed:" << query.lastError().text();
                result = -1;
            }
        }
        else
        {
            // 行数不为1，报错
            qDebug() << "查询错误：" << rowCount << "不存在这一行：" << user_uuid_;
            result = -2;
        }
    }
    else
    {
        // 查询执行失败，输出错误信息
        qDebug() << "计数查询失败:" << query.lastError().text();
    }
    return result;
}

int DataManage::InitRoleRemoteData()
{
    int result = -1;

    return result;
}

QJsonObject DataManage::GetRemoteRoleInfo()
{
    QJsonObject role_info_data;
    QString msg;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    QString query_str = "SELECT role_name, role_life, role_prestige, role_aptitude, role_exp, role_agg, "
                        "role_def, role_hp, role_cur_exp, role_lv FROM user_role_info WHERE uuid = :UUID";
    query.prepare(query_str);
    query.bindValue(":UUID", user_uuid_);
    if (query.exec())
    {
        if (query.next())
        {

            role_info_data["role_name"] = query.value("role_name").toString();
            role_info_data["role_life"] = query.value("role_life").toInt();
            role_info_data["role_prestige"] = query.value("role_prestige").toInt();
            role_info_data["role_aptitude"] = query.value("role_aptitude").toInt();
            role_info_data["role_exp"] = query.value("role_exp").toInt();
            role_info_data["role_agg"] = query.value("role_agg").toInt();
            role_info_data["role_def"] = query.value("role_def").toInt();
            role_info_data["role_hp"] = query.value("role_hp").toInt();
            role_info_data["role_cur_exp"] = query.value("role_cur_exp").toInt();
            role_info_data["role_lv"] = query.value("role_lv").toInt();
            msg = "成功获取到角色基本信息";
        }
        else
        {
            msg = "角色基本信息不存在这一行";
        }
    }
    else
    {
        msg = "角色基本信息查询失败";
    }
    qDebug() << msg;
    return role_info_data;
}

QJsonObject DataManage::GetRemoteRoleEquip()
{
    QJsonObject role_equip_data;
    return role_equip_data;
}

QJsonObject DataManage::GetRemoteRoleRC()
{
    QJsonObject role_rc_data;
    QString msg;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    QString query_str = "SELECT rc_life, rc_basic_event, rc_att_event, rc_survive_disaster, rc_prestige_event, rc_special_event "
                        "FROM user_role_rc WHERE uuid = :UUID";
    query.prepare(query_str);
    query.bindValue(":UUID", user_uuid_);
    if (query.exec())
    {
        if (query.next())
        {
            role_rc_data["rc_life"] = query.value("rc_life").toInt();
            role_rc_data["rc_basic_event"] = query.value("rc_basic_event").toInt();
            role_rc_data["rc_att_event"] = query.value("rc_att_event").toInt();
            role_rc_data["rc_survive_disaster"] = query.value("rc_survive_disaster").toInt();
            role_rc_data["rc_prestige_event"] = query.value("rc_prestige_event").toInt();
            role_rc_data["rc_special_event"] = query.value("rc_special_event").toInt();
            msg = "成功获取到角色RC信息";
        }
        else
        {
            msg = "角色RC信息不存在这一行";
        }
    }
    else
    {
        msg = "角色RC信息查询失败";
    }
    qDebug() << msg;
    return role_rc_data;
}

QJsonObject DataManage::GetRemoteRoleItem()
{
    QJsonObject role_item_data;
    QString msg;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    QString query_str = "SELECT role_money, rename_card "
                        "FROM user_role_item WHERE uuid = :UUID";
    query.prepare(query_str);
    query.bindValue(":UUID", user_uuid_);
    if (query.exec())
    {
        if (query.next())
        {
            role_item_data["role_money"] = query.value("role_money").toInt();
            role_item_data["rename_card"] = query.value("rename_card").toInt();
            msg = "成功获取到角色物品信息";
        }
        else
        {
            msg = "角色物品信息不存在这一行";
        }
    }
    else
    {
        msg = "角色物品信息查询失败";
    }
    qDebug() << msg;
    return role_item_data;
}

int DataManage::IsRoleDataInited()
{
    int roleInfoCount = 0;
    int roleItemCount = 0;
    int roleRcCount = 0;
    int roleEquipCount = 0;
    QSqlDatabase db = QSqlDatabase::database(REMOTE_DB_LINKNAME);
    QSqlQuery query(db);
    // 检查user_role_info表
    QString roleInfoQuery = QString("SELECT COUNT(*) FROM user_role_info WHERE uuid = '%1'").arg(user_uuid_);
    query.prepare(roleInfoQuery);
    query.exec(); // 执行查询语句
    if (query.next())
    {
        roleInfoCount = query.value(0).toInt();
        if (roleInfoCount > 0)
        {
            qDebug() << "检测到角色信息已经初始化";
        }
    }
    else
    {
        qDebug() << "未能获取角色信息查询结果";
    }

    // 检查user_role_item表
    QString roleItemQuery = QString("SELECT COUNT(*) FROM user_role_item WHERE uuid = '%1'").arg(user_uuid_);
    query.prepare(roleItemQuery);
    query.exec(); // 执行查询语句
    if (query.next())
    {
        roleItemCount = query.value(0).toInt();
        if (roleItemCount > 0)
        {
            qDebug() << "检测到角色物品已经初始化";
        }
    }
    else
    {
        qDebug() << "未能获取查询结果";
    }

    // 检查user_role_rc表
    QString roleRcQuery = QString("SELECT COUNT(*) FROM user_role_rc WHERE uuid = '%1'").arg(user_uuid_);
    query.prepare(roleRcQuery);
    query.exec(); // 执行查询语句
    if (query.next())
    {
        roleRcCount = query.value(0).toInt();
        if (roleRcCount > 0)
        {
            qDebug() << "检测到角色成长信息已经初始化";
        }
    }
    else
    {
        qDebug() << "未能获取查询结果";
    }

    // 检查user_role_equip表
    QString roleEquipQuery = QString("SELECT COUNT(*) FROM user_role_equip WHERE uuid = '%1'").arg(user_uuid_);
    query.prepare(roleEquipQuery);
    query.exec(); // 执行查询语句
    if (query.next())
    {
        roleEquipCount = query.value(0).toInt();
        if (roleEquipCount > 0)
        {
            qDebug() << "检测到角色装备已经初始化";
        }
    }
    else
    {
        qDebug() << "未能获取查询结果";
    }
    if(roleInfoCount > 0 && roleItemCount > 0 && roleRcCount > 0 && roleEquipCount > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
