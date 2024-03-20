#include "data_service.h"
#include "modules/public/public_declare.h"

QMutex DataService::mutex;  // 初始化互斥锁对象
QString DataService::user_uuid_ = "";
QString DataService::user_ip_  = "";
QSettings* DataService::file_setting_ = nullptr;

DataService::DataService()
{
    user_uuid_ = "";
    InitSettingFile();

#if  DATABASE_TYPE == 1
    InitLocalData();
#elif DATABASE_TYPE == 0
    InitRemoteData();
#elif DATABASE_TYPE == 2

#endif
}

DataService::~DataService()
{
    SetGameConfigInfo();
    if(file_setting_ != nullptr)
    {
        delete file_setting_;
        file_setting_ = nullptr;
    }
}

void DataService::OpenDatabase(QString path)
{
    // 打开现有数据库连接
    QSqlDatabase database_;
    database_ = QSqlDatabase::addDatabase("QSQLITE", LOCAL_DB_LINKNAME);
    database_.setDatabaseName(path);
    database_.setPassword(LOCAL_DB_PASSWORD);
    m_database_ = QSqlDatabase::database(LOCAL_DB_LINKNAME);;
    // 打开数据库连接
    if (!m_database_.open())
    {
        LOG_DEBUG(kDataManage, QString("无法打开数据库:%1").arg(m_database_.lastError().text()));
    }
    else
    {
        m_database_.exec("PRAGMA encoding = \"UTF-8\";");
        LOG_DEBUG(kDataManage, "本地数据库已经打开");
        if(!CheckTablesExist()) //检查并创建表单
        {
            LOG_DEBUG(kDataManage, "检查表单时出现错误");
        };
    }
}

void DataService::CreateDatabase(QString path)
{
    // 创建数据库连接
    QSqlDatabase database_;
    database_ = QSqlDatabase::addDatabase("QSQLITE", LOCAL_DB_LINKNAME);
    database_.setDatabaseName(path);
    database_.setPassword(LOCAL_DB_PASSWORD);
    m_database_ = QSqlDatabase::database(LOCAL_DB_LINKNAME);;

    // 打开数据库连接
    if (!m_database_.open())
    {
        LOG_DEBUG(kDataManage, QString("创建数据库失败:%1").arg(m_database_.lastError().text()));
    }
    else
    {
        LOG_DEBUG(kDataManage, "本地数据库已经打开");
        m_database_.exec("PRAGMA encoding = \"UTF-8\";");
        if(!CheckTablesExist()) //检查并创建表单
        {
            LOG_DEBUG(kDataManage, "创建数据库时，创建表单出现错误");
        };
    }
    // database_.close();
}

bool DataService::CheckTablesExist()
{
    // 检查 RoleInfo 表是否存在
    QString queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleInfo'";
    QSqlQuery query(m_database_);
    if (!query.exec(queryString))
    {
        LOG_DEBUG(kDataManage, QString("执行查询 RoleInfo 时出错:%1").arg(query.lastError().text()));
        return false;
    }
    // 如果 RoleInfo 表不存在，则创建表
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleInfo ("
                                   "role_name TEXT,"
                                   "role_life INTEGER,"
                                   "role_max_life INTEGER,"
                                   "role_prestige INTEGER,"
                                   "role_exp INTEGER,"
                                   "role_agg INTEGER,"
                                   "role_def INTEGER,"
                                   "role_hp INTEGER,"
                                   "role_cur_exp INTEGER,"
                                   "role_lv INTEGER,"
                                   "role_aptitude INTEGER"
                                   ")";
        query.prepare(createTableQuery);
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(kDataManage, QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }
        // 插入初始值
        QString insertQuery = "INSERT INTO RoleInfo (role_name, role_life, role_max_life, role_prestige, role_exp, "
                              "role_agg, role_def, role_hp, role_cur_exp, role_lv, role_aptitude) "
                              "VALUES (:role_name, :role_life, :role_max_life, :role_prestige, :role_exp, :role_agg,"
                              " :role_def, :role_hp, :role_cur_exp, :role_lv, :role_aptitude)";
        query.prepare(insertQuery);
        query.bindValue(":role_name", "GM姜子牙");
        query.bindValue(":role_life", 10);
        query.bindValue(":role_max_life", 80);
        query.bindValue(":role_prestige", 0);
        query.bindValue(":role_exp", 0);
        query.bindValue(":role_agg", 50);
        query.bindValue(":role_def", 40);
        query.bindValue(":role_hp", 300);
        query.bindValue(":role_cur_exp", 1000);
        query.bindValue(":role_lv", 1);
        query.bindValue(":role_aptitude", 1);

        if (!query.exec())
        {
            LOG_DEBUG(kDataManage, QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }
    // 检查 RoleAtt 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleAtt'";
    if (!query.exec(queryString))
    {
        LOG_DEBUG(kDataManage, QString("执行查询 RoleAtt 时出错:%1").arg(query.lastError().text()));
        return false;
    }

    // 如果 RoleAtt 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleAtt ("
                                   "role_name TEXT,"
                                   "att_metal INTEGER,"
                                   "att_wood INTEGER,"
                                   "att_water INTEGER,"
                                   "att_fire INTEGER,"
                                   "att_earth INTEGER"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(kDataManage, QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleAtt (role_name, att_metal, att_wood, att_water, att_fire, att_earth) "
                              "VALUES (:role_name, :att_metal, :att_wood, :att_water, :att_fire, :att_earth)";
        query.prepare(insertQuery);
        query.bindValue(":role_name", "GM姜子牙");
        query.bindValue(":att_metal", 0);
        query.bindValue(":att_wood", 0);
        query.bindValue(":att_water", 0);
        query.bindValue(":att_fire", 0);
        query.bindValue(":att_earth", 0);
        if (!query.exec())
        {
            LOG_DEBUG(kDataManage, QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }

    // 检查 RoleEquip 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleEquip'";
    if (!query.exec(queryString))
    {
        LOG_DEBUG(kDataManage, QString("执行查询 RoleEquip 时出错:%1").arg(query.lastError().text()));
        return false;
    }

    // 如果 RoleEquip 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleEquip ("
                                   "role_name TEXT,"
                                   "equip_title TEXT,"
                                   "equip_weapon TEXT,"
                                   "equip_magic TEXT,"
                                   "equip_helmet TEXT,"
                                   "equip_clothing TEXT,"
                                   "equip_britches TEXT,"
                                   "equip_shoe TEXT,"
                                   "equip_jewelry TEXT,"
                                   "equip_mount TEXT"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(kDataManage, QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleEquip (role_name, equip_title, equip_weapon, equip_magic, equip_helmet, "
                              "equip_clothing, equip_britches, equip_shoe, equip_jewelry, equip_mount) "
                              "VALUES (:role_name, :equip_title, :equip_weapon, :equip_magic, :equip_helmet, "
                              ":equip_clothing, :equip_britches, :equip_shoe, :equip_jewelry, :equip_mount)";
        query.prepare(insertQuery);
        query.bindValue(":role_name", "GM姜子牙");
        query.bindValue(":equip_title", "乐善好施");
        query.bindValue(":equip_weapon", "闪光机械键盘");
        query.bindValue(":equip_magic", "陈年保温杯");
        query.bindValue(":equip_helmet", "洪荒盔");
        query.bindValue(":equip_clothing", "洪荒甲");
        query.bindValue(":equip_britches", "洪荒腰带");
        query.bindValue(":equip_shoe", "洪荒靴");
        query.bindValue(":equip_jewelry", "地摊项链");
        query.bindValue(":equip_mount", "哈士奇");
        if (!query.exec())
        {
            LOG_DEBUG(kDataManage, QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }

    // 检查 RoleItemEnum 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleItem'";
    if (!query.exec(queryString))
    {
        LOG_DEBUG(kDataManage, QString("执行查询 RoleItem 时出错:%1").arg(query.lastError().text()));
        return false;
    }

    // 如果 RoleItem 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleItem ("
                                   "role_name TEXT,"
                                   "10001 INTEGER"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(kDataManage, QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleItem (role_name, 10001) "
                              "VALUES (:role_name, :10001)";
        query.prepare(insertQuery);
        query.bindValue(":role_name", "GM姜子牙");
        query.bindValue(":10001", 0);
        if (!query.exec())
        {
            LOG_DEBUG(kDataManage, QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }

    // 检查 RoleCoefficient 表是否存在 角色各项系数
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleCoefficient'";
    if (!query.exec(queryString))
    {
        LOG_DEBUG(kDataManage, QString("执行查询 RoleCoefficient 时出错:%1").arg(query.lastError().text()));
        return false;
    }

    // 如果 RoleCoefficient 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleCoefficient ("
                                   "role_name TEXT,"
                                   "RC_life INTEGER,"
                                   "RC_basic_event INTEGER,"
                                   "RC_att_event INTEGER,"
                                   "RC_survive_disaster INTEGER,"
                                   "RC_prestige_event INTEGER,"
                                   "RC_special_event INTEGER"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(kDataManage, QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleCoefficient (role_name, RC_life, RC_basic_event, RC_att_event, "
                              "RC_survive_disaster, RC_prestige_event, RC_special_event) "
                              "VALUES (:role_name, :RC_life, :RC_basic_event, :RC_attEvent, :RC_survive_disaster,"
                              " :RC_prestige_event, :RC_special_event)";
        query.prepare(insertQuery);
        query.bindValue(":role_name", "GM姜子牙");
        query.bindValue(":RC_life", 1);
        query.bindValue(":RC_basic_event", 1);
        query.bindValue(":RC_att_event", 1);
        query.bindValue(":RC_survive_disaster", 0);
        query.bindValue(":RC_prestige_event", 1);
        query.bindValue(":RC_special_event", 1);
        if (!query.exec())
        {
            LOG_DEBUG(kDataManage, QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }
    return true;
}

QString DataService::GetTableToInfo(QString table_name, QString column_name)
{
    QString result = "";
    if(!m_database_.isOpen())
    {
        LOG_DEBUG(kDataManage, "数据库打开失败");
        return result;
    }
    else
    {
        QSqlQuery query(m_database_);
        QString queryString = QString("SELECT %1 FROM %2").arg(column_name, table_name);
        if (!query.exec(queryString))
        {
            LOG_DEBUG(kDataManage, queryString);
            LOG_DEBUG(kDataManage, QString("执行查询时出错:%1").arg(query.lastError().text()));
        }
        else
        {
            if (query.next())
            {
                QString log = table_name + " 查询数据为：" + column_name + " ：" + query.value(0).toString();
                LOG_DEBUG(kDataManage, log);
                result = query.value(0).toString();
            }
        }
        return result;
    }
}

void DataService::DatabaseClose()
{
    // database_.close();
}

void DataService::SlotSaveRoleInfoToDatabase(const QJsonObject& role_data)
{
    is_SaveRoleInfo = true;
    role_data_ = role_data;
    start();
}

void DataService::SlotSaveRoleItemToDatabase(const QJsonObject& role_item_data)
{
    is_SaveRoleItem = true;
    role_item_data_ = role_item_data;
    start();
}

void DataService::SlotSaveRoleEquipToDatabase(const QJsonObject& role_equip_data)
{
    is_SaveRoleEquip = true;
    role_equip_data_ = role_equip_data;
    start();
}

void DataService::SlotSaveRoleCoefficientToDatabase(const QJsonObject& RC_data)
{
    is_SaveRoleCoefficient = true;
    RC_data_ = RC_data;
    start();
}

void DataService::SlotUpdataLoginLog()
{
    // 账号信息 登录时间 IP UUID 角色名 等级
    is_SaveLoginLog = true;
    start();
}

void DataService::WriteRoleInfoToLocalDatabase()
{
    if(m_database_.isOpen())
    {
        QString role_name = role_data_.value("role_name").toString();
        role_item_data_.remove("role_name");
        QSqlQuery query(m_database_);
        // 开始构建更新查询语句
        QString updateQuery = "UPDATE RoleInfo SET ";
        // 遍历role_item_data中的键值对
        QStringList updateValues;
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            QString key = it.key();
//            QString value = it.value().toString();

            // 将键值对添加到更新语句中
            updateValues.append(key + " = :" + key);
        }

        // 将更新的键值对连接到查询语句中
        updateQuery += updateValues.join(", ");
        updateQuery += " WHERE role_name = :role_name";
        LOG_DEBUG(kDataManage, QString("查询语句：%1").arg(updateQuery));
        // 准备查询
        query.prepare(updateQuery);

        // 绑定roleName参数
        query.bindValue(":role_name", role_name_);

        // 绑定role_item_data中的键值对
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            query.bindValue(":" + it.key(), it.value().toString());
        }
        // 执行查询
        if (!query.exec())
        {
            LOG_DEBUG(kDataManage, QString("更新操作失败：%1").arg(query.lastError().text()));
        }
    }
    else
    {
        LOG_DEBUG(kDataManage, "数据库未打开");
    }
}

void DataService::WriteRoleItemsToLocalDatabase()
{
    if(m_database_.isOpen())
    {
        QString roleName = role_item_data_.value("role_name").toString();
        role_item_data_.remove("role_name");

        QSqlQuery query(m_database_);
        // 开始构建更新查询语句
        QString updateQuery = "UPDATE RoleItem SET ";

        // 遍历role_item_data中的键值对
        QStringList updateValues;
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            QString key = it.key();
//            QString value = it.value().toString();

            // 将键值对添加到更新语句中
            updateValues.append(key + " = :" + key);
        }

        // 将更新的键值对连接到查询语句中
        updateQuery += updateValues.join(", ");
        updateQuery += " WHERE role_name = :role_name";
        LOG_DEBUG(kDataManage, QString("查询语句：%1").arg(updateQuery));
        // 准备查询
        query.prepare(updateQuery);

        // 绑定roleName参数
        query.bindValue(":roleName", role_name_);

        // 绑定role_item_data中的键值对
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            query.bindValue(":" + it.key(), it.value().toString());
        }
        // 执行查询
        if (!query.exec())
        {
            LOG_DEBUG(kDataManage, QString("更新操作失败：%1").arg(query.lastError().text()));
        }
    }
    else
    {
        LOG_DEBUG(kDataManage, "数据库未打开");
    }
}

void DataService::WriteRoleEquipToLocalDatabase()
{
    if(m_database_.isOpen())
    {
        QString roleName = role_equip_data_.value("role_name").toString();
        role_equip_data_.remove("role_name");

        QSqlQuery query(m_database_);
        // 开始构建更新查询语句
        QString updateQuery = "UPDATE RoleEquip SET ";

        // 遍历role_item_data中的键值对
        QStringList updateValues;
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            QString key = it.key();
//            QString value = it.value().toString();

            // 将键值对添加到更新语句中
            updateValues.append(key + " = :" + key);
        }

        // 将更新的键值对连接到查询语句中
        updateQuery += updateValues.join(", ");
        updateQuery += " WHERE role_name = :role_name";
        LOG_DEBUG(kDataManage, QString("查询语句：%1").arg(updateQuery));
        // 准备查询
        query.prepare(updateQuery);

        // 绑定roleName参数
        query.bindValue(":role_name", role_name_);

        // 绑定role_item_data中的键值对
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            query.bindValue(":" + it.key(), it.value().toString());
        }
        // 执行查询
        if (!query.exec())
        {
            LOG_DEBUG(kDataManage, QString("更新操作失败：%1").arg(query.lastError().text()));
        }
    }
    else
    {
        LOG_DEBUG(kDataManage, "数据库未打开");
    }
}

void DataService::WriteRoleCoefficientToLocalDatabase()
{
    if(m_database_.isOpen())
    {
        QString roleName = RC_data_.value("role_name").toString();

        QSqlQuery query(m_database_);
        query.prepare("SELECT COUNT(*) FROM Role_coefficient WHERE role_name = :role_name");
        query.bindValue(":role_name", role_name_);

        if (query.exec() && query.next())
        {
            int rowCount = query.value(0).toInt();
            if (rowCount > 0)
            {
                // 执行更新操作
                QString updateQuery = "UPDATE RoleCoefficient SET RC_life = :RC_life, RC_basic_event = :RC_basic_event, RC_att_event = :RC_att_event, RC_survive_disaster = :RC_survive_disaster"
                                      ", RC_prestige_event = :RC_prestige_event, RC_special_event = :RC_special_event WHERE role_name = :role_name";
                query.prepare(updateQuery);
            }
            else
            {
                // 执行插入操作
                QString insertQuery = "INSERT INTO RoleCoefficient (role_name,  RC_life, RC_basic_event, RC_att_event, RC_survive_disaster, RC_prestige_event, RC_special_event) "
                                      "VALUES (:role_name, :RC_life, :RC_basic_event, :RC_att_event, :RC_survive_disaster, :RC_prestige_event, :RC_special_event)";
                query.prepare(insertQuery);
            }

            query.bindValue(":role_name", role_name_);
            query.bindValue(":RC_life", RC_data_.value("RC_life").toInt());
            query.bindValue(":RC_basic_event", RC_data_.value("RC_basic_event").toInt());
            query.bindValue(":RC_att_event", RC_data_.value("RC_att_event").toInt());
            query.bindValue(":RC_survive_disaster", RC_data_.value("RC_survive_disaster").toInt());
            query.bindValue(":RC_prestige_event", RC_data_.value("RC_prestige_event").toInt());
            query.bindValue(":RC_special_event", RC_data_.value("RC_special_event").toInt());
            if (!query.exec())
            {
                LOG_DEBUG(kDataManage, QString("保存数据时出错:%1").arg(query.lastError().text()));
                return;
            }
        }
    }
    else
    {
        LOG_DEBUG(kDataManage, "数据库未打开");
    }
}

void DataService::run()
{
    QMutexLocker locker(&mutex);
//    InitRemoteData();
#if DATABASE_TYPE == 0
    if(is_SaveRoleInfo)
    {
        is_SaveRoleInfo = false;
        WriteRoleInfoToRemoteDatabase();
    }
    if(is_SaveRoleItem)
    {
        is_SaveRoleItem = false;
        WriteRoleItemsToRemoteDatabase();
    }
    if(is_SaveRoleCoefficient)
    {
        is_SaveRoleCoefficient = false;
        WriteRoleCoefficientToRemoteDatabase();
    }
    if(is_SaveLoginLog)
    {
        is_SaveLoginLog = false;
        WriteUserLoginLogToRemoteDatabase();
    }

#elif DATABASE_TYPE == 1
    if(is_SaveRoleInfo)
    {
        is_SaveRoleInfo = false;
        WriteRoleInfoToLocalDatabase();
    }
    if(is_SaveRoleItem)
    {
        is_SaveRoleItem = false;
        WriteRoleItemsToLocalDatabase();
    }
    if(is_SaveRoleCoefficient)
    {
        is_SaveRoleCoefficient = false;
        WriteRoleCoefficientToLocalDatabase();
    }
    if(is_SaveRoleEquip)
    {
        is_SaveRoleEquip = false;
        WriteRoleEquipToLocalDatabase();
    }
#elif DATABASE_TYPE == 2
#endif
}

QJsonObject DataService::InitLocalRoleInfo() {
    QString last_game_time = "最近一次离线时间是：" + GetLastGameTime();
    QJsonObject data_obj;
    data_obj.insert("msg", last_game_time);
    emit SignalActionRequest(PublicFunc::PackageRequest(uiCmd::ShowMsgToUI,
                                                        data_obj,
                                                         "",
                                                         module_name::ui,
                                                         module_name::data));
//    emit SignalShowMsgToUI(last_game_time);
    QString name = GetTableToInfo("RoleInfo", "role_name");
    QString life = GetTableToInfo("RoleInfo", "role_life");
    QString max_life = GetTableToInfo("RoleInfo", "role_max_life");
    QString prestige = GetTableToInfo("RoleInfo", "role_prestige");
    QString LV = GetTableToInfo("RoleInfo", "role_lv");
    int cultivation = LV.toInt();
    QString cur_exp = GetTableToInfo("RoleInfo", "role_cur_exp");
    QString exp = GetTableToInfo("RoleInfo", "role_exp");
    QString agg = GetTableToInfo("RoleInfo", "role_agg");
    QString def = GetTableToInfo("RoleInfo", "role_def");
    QString hp = GetTableToInfo("RoleInfo", "role_hp");
    QString aptitude = GetTableToInfo("RoleInfo", "role_aptitude");

    // 从数据库获取角色获取装备
    QString weapon = GetTableToInfo("RoleEquip", "equip_weapon");
    QString magic = GetTableToInfo("RoleEquip", "equip_magic");
    QString helmet = GetTableToInfo("RoleEquip", "equip_helmet");
    QString clothing = GetTableToInfo("RoleEquip", "equip_clothing");
    QString britches = GetTableToInfo("RoleEquip", "equip_britches");
    QString shoe = GetTableToInfo("RoleEquip", "equip_shoe");
    QString jewelry = GetTableToInfo("RoleEquip", "equip_jewelry");
    QString mount = GetTableToInfo("RoleEquip", "equip_mount");
    QString title = GetTableToInfo("RoleEquip", "equip_title");

    // 从数据库获取角色获取物品、道具
    QString money = GetTableToInfo("RoleItem", "10001");

    // 从数据库获取角色属性相关系数
    QString life_Coefficient = GetTableToInfo("RoleCoefficient", "RC_life");
    QString RC_survive_disaster = GetTableToInfo("RoleCoefficient", "RC_survive_disaster");
    QString RC_prestige_event = GetTableToInfo("RoleCoefficient", "RC_prestige_event");
    QString RC_special_event = GetTableToInfo("RoleCoefficient", "RC_special_event");
    QJsonObject role_info, role_equip, role_item, role_coefficient, obj_;
    role_info.insert("role_name", name);
    role_info.insert("role_life", life);
    role_info.insert("role_max_life", max_life);
    role_info.insert("role_prestige", prestige);
    role_info.insert("role_lv", cultivation);
    role_info.insert("role_cur_exp", cur_exp);
    role_info.insert("role_exp", exp);
    role_info.insert("role_agg", agg);
    role_info.insert("role_def", def);
    role_info.insert("role_hp", hp);
    role_info.insert("role_aptitude", aptitude);

    role_equip.insert("equip_weapon", weapon);
    role_equip.insert("equip_magic", magic);
    role_equip.insert("equip_helmet", helmet);
    role_equip.insert("equip_clothing", clothing);
    role_equip.insert("equip_britches", britches);
    role_equip.insert("equip_shoe", shoe);
    role_equip.insert("equip_jewelry", jewelry);
    role_equip.insert("equip_mount", mount);
    role_equip.insert("equip_title", title);

    role_coefficient.insert("RC_life", life_Coefficient);
    role_coefficient.insert("RC_survive_disaster", RC_survive_disaster);
    role_coefficient.insert("RC_prestige_event", RC_prestige_event);
    role_coefficient.insert("RC_special_event", RC_special_event);

    obj_.insert("RoleInfo", role_info);
    obj_.insert("RoleEquip", role_equip);
    obj_.insert("RoleItem", role_item);
    obj_.insert("RoleCoefficient", role_coefficient);

    // 更新角色信息
    emit SignalActionRequest(PublicFunc::PackageRequest(mainCmd::InitLocalRoleInfo,
                                                        data_obj,
                                                        "",
                                                        module_name::role,
                                                        module_name::data));

    // 更新道具
    emit SignalActionRequest(PublicFunc::PackageRequest(mainCmd::InitLocalRoleInfo,
                                                        data_obj,
                                                        "",
                                                        module_name::item,
                                                        module_name::data));
    // 更新UI
    emit SignalActionRequest(PublicFunc::PackageRequest(mainCmd::InitLocalRoleInfo,
                                                        data_obj,
                                                        "",
                                                        module_name::ui,
                                                        module_name::data));
}

void DataService::SetRoleName(QString name) {
    role_name_ = name;
}
