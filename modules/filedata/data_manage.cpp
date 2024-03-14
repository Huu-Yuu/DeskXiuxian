#include "data_manage.h"

QMutex DataManage::mutex;  // 初始化互斥锁对象
QString DataManage::user_uuid_ = "";
QString DataManage::user_ip_  = "";
QSettings* DataManage::file_setting_ = nullptr;

DataManage::DataManage()
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

DataManage::~DataManage()
{
    SetGameConfigInfo();
    if(file_setting_ != nullptr)
    {
        delete file_setting_;
        file_setting_ = nullptr;
    }
}

void DataManage::OpenDatabase(QString path)
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
        LOG_DEBUG(QString("无法打开数据库:%1").arg(m_database_.lastError().text()));
    }
    else
    {
        m_database_.exec("PRAGMA encoding = \"UTF-8\";");
        LOG_DEBUG("本地数据库已经打开");
        if(!CheckTablesExist()) //检查并创建表单
        {
            LOG_DEBUG("检查表单时出现错误");
        };
    }
}

void DataManage::CreateDatabase(QString path)
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
        LOG_DEBUG(QString("创建数据库失败:%1").arg(m_database_.lastError().text()));
    }
    else
    {
        LOG_DEBUG("本地数据库已经打开");
        m_database_.exec("PRAGMA encoding = \"UTF-8\";");
        if(!CheckTablesExist()) //检查并创建表单
        {
            LOG_DEBUG("创建数据库时，创建表单出现错误");
        };
    }
    // database_.close();
}

bool DataManage::CheckTablesExist()
{
    // 检查 RoleInfo 表是否存在
    QString queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleInfo'";
    QSqlQuery query(m_database_);
    if (!query.exec(queryString))
    {
        LOG_DEBUG(QString("执行查询 RoleInfo 时出错:%1").arg(query.lastError().text()));
        return false;
    }
    // 如果 RoleInfo 表不存在，则创建表
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleInfo ("
                                   "roleUUID TEXT,"
                                   "roleName TEXT,"
                                   "roleLife INTEGER,"
                                   "roleMaxLife INTEGER,"
                                   "rolePrestige INTEGER,"
                                   "roleExp INTEGER,"
                                   "roleAgg INTEGER,"
                                   "roleDef INTEGER,"
                                   "roleHp INTEGER,"
                                   "roleCurExp INTEGER,"
                                   "roleLv INTEGER"
                                   ")";
        query.prepare(createTableQuery);
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }
        // 插入初始值
        QString insertQuery = "INSERT INTO RoleInfo (roleUUID, roleName, roleLife, roleMaxLife, rolePrestige, roleExp, roleAgg, roleDef, roleHp, roleCurExp, roleLv) "
                              "VALUES (:roleUUID, :roleName, :roleLife, :roleMaxLife, :rolePrestige, :roleExp, :roleAgg, :roleDef, :roleHp, :roleCurExp, :roleLv)";
        query.prepare(insertQuery);
        query.bindValue(":roleUUID", "UUID");
        query.bindValue(":roleName", "GM姜子牙");
        query.bindValue(":roleLife", 10);
        query.bindValue(":roleMaxLife", 80);
        query.bindValue(":rolePrestige", 0);
        query.bindValue(":roleExp", 0);
        query.bindValue(":roleAgg", 50);
        query.bindValue(":roleDef", 40);
        query.bindValue(":roleHp", 300);
        query.bindValue(":roleCurExp", 1000);
        query.bindValue(":roleLv", 1);

        if (!query.exec())
        {
            LOG_DEBUG(QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }
    // 检查 RoleAtt 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleAtt'";
    if (!query.exec(queryString))
    {
        LOG_DEBUG(QString("执行查询 RoleAtt 时出错:%1").arg(query.lastError().text()));
        return false;
    }

    // 如果 RoleAtt 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleAtt ("
                                   "roleUUID TEXT,"
                                   "roleName TEXT,"
                                   "attMetal INTEGER,"
                                   "attWood INTEGER,"
                                   "attWater INTEGER,"
                                   "attFire INTEGER,"
                                   "attEarth INTEGER"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleAtt (roleUUID, roleName, attMetal, attWood, attWater, attFire, attEarth) "
                              "VALUES (:roleUUID, :roleName, :attMetal, :attWood, :attWater, :attFire, :attEarth)";
        query.prepare(insertQuery);
        query.bindValue(":roleUUID", "UUID");
        query.bindValue(":roleName", "GM姜子牙");
        query.bindValue(":attMetal", 0);
        query.bindValue(":attWood", 0);
        query.bindValue(":attWater", 0);
        query.bindValue(":attFire", 0);
        query.bindValue(":attEarth", 0);
        if (!query.exec())
        {
            LOG_DEBUG(QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }

    // 检查 RoleEquip 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleEquip'";
    if (!query.exec(queryString))
    {
        LOG_DEBUG(QString("执行查询 RoleEquip 时出错:%1").arg(query.lastError().text()));
        return false;
    }

    // 如果 RoleEquip 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleEquip ("
                                   "roleUUID TEXT,"
                                   "roleName TEXT,"
                                   "equipTitle TEXT,"
                                   "equipWeapon TEXT,"
                                   "equipMagic TEXT,"
                                   "equipHelmet TEXT,"
                                   "equipClothing TEXT,"
                                   "equipBritches TEXT,"
                                   "equipShoe TEXT,"
                                   "equipJewelry TEXT,"
                                   "equipMount TEXT"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleEquip (roleUUID, roleName, equipTitle, equipWeapon, equipMagic, equipHelmet, equipClothing, equipBritches, equipShoe, equipJewelry, equipMount) "
                              "VALUES (:roleUUID, :roleName, :equipTitle, :equipWeapon, :equipMagic, :equipHelmet, :equipClothing, :equipBritches, :equipShoe, :equipJewelry, :equipMount)";
        query.prepare(insertQuery);
        query.bindValue(":roleUUID", "UUID");
        query.bindValue(":roleName", "GM姜子牙");
        query.bindValue(":equipTitle", "乐善好施");
        query.bindValue(":equipWeapon", "闪光机械键盘");
        query.bindValue(":equipMagic", "陈年保温杯");
        query.bindValue(":equipHelmet", "洪荒盔");
        query.bindValue(":equipClothing", "洪荒甲");
        query.bindValue(":equipBritches", "洪荒腰带");
        query.bindValue(":equipShoe", "洪荒靴");
        query.bindValue(":equipJewelry", "地摊项链");
        query.bindValue(":equipMount", "哈士奇");
        if (!query.exec())
        {
            LOG_DEBUG(QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }

    // 检查 RoleItemEnum 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleItemEnum'";
    if (!query.exec(queryString))
    {
        LOG_DEBUG(QString("执行查询 RoleItemEnum 时出错:%1").arg(query.lastError().text()));
        return false;
    }

    // 如果 RoleItemEnum 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleItemEnum ("
                                   "roleUUID TEXT,"
                                   "roleName TEXT,"
                                   "roleMoney INTEGER"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleItemEnum (roleUUID, roleName, roleMoney) "
                              "VALUES (:roleUUID, :roleName, :roleMoney)";
        query.prepare(insertQuery);
        query.bindValue(":roleUUID", "UUID");
        query.bindValue(":roleName", "GM姜子牙");
        query.bindValue(":roleMoney", 100);
        if (!query.exec())
        {
            LOG_DEBUG(QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }

    // 检查 RoleCoefficient 表是否存在 角色各项系数
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleCoefficient'";
    if (!query.exec(queryString))
    {
        LOG_DEBUG(QString("执行查询 RoleCoefficient 时出错:%1").arg(query.lastError().text()));
        return false;
    }

    // 如果 RoleCoefficient 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleCoefficient ("
                                   "roleUUID TEXT,"
                                   "roleName TEXT,"
                                   "RCLife INTEGER,"
                                   "RCBasicEvent INTEGER,"
                                   "RCAttEvent INTEGER,"
                                   "RCSurviveDisaster INTEGER,"
                                   "RCPrestigeEvent INTEGER,"
                                   "RCSpecialEvent INTEGER,"
                                   "roleAptitude INTEGER"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            LOG_DEBUG(QString("创建表时出错:%1").arg(query.lastError().text()));
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleCoefficient (roleUUID, roleName, RCLife, RCBasicEvent, RCAttEvent, "
                              "RCSurviveDisaster, RCPrestigeEvent, RCSpecialEvent, roleAptitude) "
                              "VALUES (:roleUUID, :roleName, :RCLife, :RCBasicEvent, :RCAttEvent, :RCSurviveDisaster,"
                              " :RCPrestigeEvent, :RCSpecialEvent, :roleAptitude)";
        query.prepare(insertQuery);
        query.bindValue(":roleUUID", "UUID");
        query.bindValue(":roleName", "GM姜子牙");
        query.bindValue(":RCLife", 1);
        query.bindValue(":RCBasicEvent", 1);
        query.bindValue(":RCAttEvent", 1);
        query.bindValue(":RCSurviveDisaster", 0);
        query.bindValue(":RCPrestigeEvent", 1);
        query.bindValue(":RCSpecialEvent", 1);
        query.bindValue(":roleAptitude", 1);
        if (!query.exec())
        {
            LOG_DEBUG(QString("插入初始值时出错:%1").arg(query.lastError().text()));
            return false;
        }
    }
    return true;
}

QString DataManage::GetTableToInfo(QString table_name, QString column_name)
{
    QString result = "";
    if(!m_database_.isOpen())
    {
        LOG_DEBUG("数据库打开失败");
        return result;
    }
    else
    {
        QSqlQuery query(m_database_);
        QString queryString = QString("SELECT %1 FROM %2").arg(column_name, table_name);
        if (!query.exec(queryString))
        {
            LOG_DEBUG(queryString);
            LOG_DEBUG(QString("执行查询时出错:%1").arg(query.lastError().text()));
        }
        else
        {
            if (query.next())
            {
                QString log = table_name + " 查询数据为：" + column_name + " ：" + query.value(0).toString();
                LOG_DEBUG(log);
                result = query.value(0).toString();
            }
        }
        return result;
    }
}

void DataManage::DatabaseClose()
{
    // database_.close();
}

void DataManage::SlotSaveRoleInfoToDatabase(const QJsonObject& role_data)
{
    is_SaveRoleInfo = true;
    role_data_ = role_data;
    start();
}

void DataManage::SlotSaveRoleItemToDatabase(const QJsonObject& role_item_data)
{
    is_SaveRoleItem = true;
    role_item_data_ = role_item_data;
    start();
}

void DataManage::SlotSaveRoleEquipToDatabase(const QJsonObject& role_equip_data)
{
    is_SaveRoleEquip = true;
    role_equip_data_ = role_equip_data;
    start();
}

void DataManage::SlotSaveRoleCoefficientToDatabase(const QJsonObject& RC_data)
{
    is_SaveRoleCoefficient = true;
    RC_data_ = RC_data;
    start();
}

void DataManage::SlotUpdataLoginLog()
{
    // 账号信息 登录时间 IP UUID 角色名 等级
    is_SaveLoginLog = true;
    start();
}

void DataManage::WriteRoleInfoToLocalDatabase()
{
    if(m_database_.isOpen())
    {
        QString roleName = role_data_.value("roleName").toString();
        role_item_data_.remove("roleName");
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
        updateQuery += " WHERE roleName = :roleName";

        // 准备查询
        query.prepare(updateQuery);

        // 绑定roleName参数
        query.bindValue(":roleName", roleName);

        // 绑定role_item_data中的键值对
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            query.bindValue(":" + it.key(), it.value().toString());
        }
        // 执行查询
        if (!query.exec())
        {
            LOG_DEBUG(QString("更新操作失败：%1").arg(query.lastError().text()));
        }
    }
    else
    {
        LOG_DEBUG("数据库未打开");
    }
}

void DataManage::WriteRoleItemsToLocalDatabase()
{
    if(m_database_.isOpen())
    {
        QString roleName = role_item_data_.value("roleName").toString();
        role_item_data_.remove("roleName");

        QSqlQuery query(m_database_);
        // 开始构建更新查询语句
        QString updateQuery = "UPDATE RoleItemEnum SET ";

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
        updateQuery += " WHERE roleName = :roleName";

        // 准备查询
        query.prepare(updateQuery);

        // 绑定roleName参数
        query.bindValue(":roleName", roleName);

        // 绑定role_item_data中的键值对
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            query.bindValue(":" + it.key(), it.value().toString());
        }
        // 执行查询
        if (!query.exec())
        {
            LOG_DEBUG(QString("更新操作失败：%1").arg(query.lastError().text()));
        }
    }
    else
    {
        LOG_DEBUG("数据库未打开");
    }
}

void DataManage::WriteRoleEquipToLocalDatabase()
{
    if(m_database_.isOpen())
    {
        QString roleName = role_item_data_.value("roleName").toString();
        role_item_data_.remove("roleName");

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
        updateQuery += " WHERE roleName = :roleName";

        // 准备查询
        query.prepare(updateQuery);

        // 绑定roleName参数
        query.bindValue(":roleName", roleName);

        // 绑定role_item_data中的键值对
        for (auto it = role_item_data_.constBegin(); it != role_item_data_.constEnd(); ++it)
        {
            query.bindValue(":" + it.key(), it.value().toString());
        }
        // 执行查询
        if (!query.exec())
        {
            LOG_DEBUG(QString("更新操作失败：%1").arg(query.lastError().text()));
        }
    }
    else
    {
        LOG_DEBUG("数据库未打开");
    }
}

void DataManage::WriteRoleCoefficientToLocalDatabase()
{
    if(m_database_.isOpen())
    {
        QString roleName = RC_data_.value("roleName").toString();

        QSqlQuery query(m_database_);
        query.prepare("SELECT COUNT(*) FROM RoleCoefficient WHERE roleName = :roleName");
        query.bindValue(":roleName", roleName);

        if (query.exec() && query.next())
        {
            int rowCount = query.value(0).toInt();
            if (rowCount > 0)
            {
                // 执行更新操作
                QString updateQuery = "UPDATE RoleCoefficient SET RCLife = :RCLife, RCBasicEvent = :RCBasicEvent, RCAttEvent = :RCAttEvent, RCSurviveDisaster = :RCSurviveDisaster"
                                      ", RCPrestigeEvent = :RCPrestigeEvent, RCSpecialEvent = :RCSpecialEvent, roleAptitude = :roleAptitude WHERE roleName = :roleName";
                query.prepare(updateQuery);
            }
            else
            {
                // 执行插入操作
                QString insertQuery = "INSERT INTO RoleCoefficient (roleName,  RCLife, RCBasicEvent, RCAttEvent, RCSurviveDisaster, RCPrestigeEvent, RCSpecialEvent, roleAptitude) "
                                      "VALUES (:roleName, :RCLife, :RCBasicEvent, :RCAttEvent, :RCPrestigeEvent, :RCSpecialEvent, :roleAptitude)";
                query.prepare(insertQuery);
            }

            query.bindValue(":roleName", roleName);
            query.bindValue(":RCLife", RC_data_.value("RCLife").toInt());
            query.bindValue(":RCBasicEvent", RC_data_.value("RCBasicEvent").toInt());
            query.bindValue(":RCAttEvent", RC_data_.value("RCAttEvent").toInt());
            query.bindValue(":RCSurviveDisaster", RC_data_.value("RCSurviveDisaster").toInt());
            query.bindValue(":RCPrestigeEvent", RC_data_.value("RCPrestigeEvent").toInt());
            query.bindValue(":RCSpecialEvent", RC_data_.value("RCSpecialEvent").toInt());
            query.bindValue(":roleAptitude", RC_data_.value("roleAptitude").toInt());
            if (!query.exec())
            {
                LOG_DEBUG(QString("保存数据时出错:%1").arg(query.lastError().text()));
                return;
            }
        }
    }
    else
    {
        LOG_DEBUG("数据库未打开");
    }
}

void DataManage::run()
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
