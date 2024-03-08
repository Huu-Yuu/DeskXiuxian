#include "datamanage.h"

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
    database_ = QSqlDatabase::addDatabase("QSQLITE");
    database_.setDatabaseName(path);
    // 打开数据库连接
    if (!database_.open())
    {
        qDebug() << "无法打开数据库:" << database_.lastError().text();
    }
    else
    {
        database_.exec("PRAGMA encoding = \"UTF-8\";");
        qDebug() << "数据库已经打开.";
        if(!CheckTablesExist()) //检查并创建表单
        {
            qDebug() << "检查表单时出现错误";
        };
    }
}

void DataManage::CreateDatabase(QString path)
{
    // 创建数据库连接
    database_ = QSqlDatabase::addDatabase("QSQLITE");
    database_.setDatabaseName(path);

    // 打开数据库连接
    if (!database_.isOpen())
    {
        qDebug() << "创建数据库失败:" << database_.lastError().text();
    }
    else
    {
        if(!CheckTablesExist()) //检查并创建表单
        {
            qDebug() << "创建数据库时，创建表单出现错误";
        };
    }
    // database_.close();
}

bool DataManage::CheckTablesExist()
{
    // 检查 RoleInfo 表是否存在

    QString queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleInfo'";
    QSqlQuery query;
    if (!query.exec(queryString))
    {
        qDebug() << "执行查询 RoleInfo 时出错:" << query.lastError().text();
        return false;
    }
    // 如果 RoleInfo 表不存在，则创建表
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleInfo ("
                                   "roleUUID TEXT,"
                                   "roleName TEXT,"
                                   "roleLife INTEGER,"
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
            qDebug() << "创建表时出错:" << query.lastError().text();
            return false;
        }
        // 插入初始值
        QString insertQuery = "INSERT INTO RoleInfo (roleUUID, roleName, roleLife, rolePrestige, roleExp, roleAgg, roleDef, roleHp, roleCurExp, roleLv) "
                              "VALUES (:roleUUID, :roleName, :roleLife, :rolePrestige, :roleExp, :roleAgg, :roleDef, :roleHp, :roleCurExp, :roleLv)";
        query.prepare(insertQuery);
        query.bindValue(":roleUUID", "UUID");
        query.bindValue(":roleName", "GM姜子牙");
        query.bindValue(":roleLife", 25);
        query.bindValue(":rolePrestige", 10);
        query.bindValue(":roleExp", 0);
        query.bindValue(":roleAgg", 50);
        query.bindValue(":roleDef", 40);
        query.bindValue(":roleHp", 300);
        query.bindValue(":roleCurExp", 1000);
        query.bindValue(":roleLv", 1);

        if (!query.exec())
        {
            qDebug() << "插入初始值时出错:" << query.lastError().text();
            return false;
        }
    }
    // 检查 RoleAtt 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleAtt'";
    if (!query.exec(queryString))
    {
        qDebug() << "执行查询 RoleAtt 时出错:" << query.lastError().text();
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
            qDebug() << "创建表时出错:" << query.lastError().text();
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
            qDebug() << "插入初始值时出错:" << query.lastError().text();
            return false;
        }
    }

    // 检查 RoleEquip 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleEquip'";
    if (!query.exec(queryString))
    {
        qDebug() << "执行查询 RoleEquip 时出错:" << query.lastError().text();
        return false;
    }

    // 如果 RoleEquip 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleEquip ("
                                   "roleUUID TEXT,"
                                   "roleName TEXT,"
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
            qDebug() << "创建表时出错:" << query.lastError().text();
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleEquip (roleUUID, roleName, equipWeapon, equipMagic, equipHelmet, equipClothing, equipBritches, equipShoe, equipJewelry, equipMount) "
                              "VALUES (:roleUUID, :roleName, :equipWeapon, :equipMagic, :equipHelmet, :equipClothing, :equipBritches, :equipShoe, :equipJewelry, :equipMount)";
        query.prepare(insertQuery);
        query.bindValue(":roleUUID", "UUID");
        query.bindValue(":roleName", "GM姜子牙");
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
            qDebug() << "插入初始值时出错:" << query.lastError().text();
            return false;
        }
    }

    // 检查 RoleItemEnum 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleItemEnum'";
    if (!query.exec(queryString))
    {
        qDebug() << "执行查询 RoleItemEnum 时出错:" << query.lastError().text();
        return false;
    }

    // 如果 RoleItemEnum 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleItemEnum ("
                                   "roleUUID TEXT,"
                                   "roleName TEXT,"
                                   "roleMoney INTEGER,"
                                   "renameCard INTEGER"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            qDebug() << "创建表时出错:" << query.lastError().text();
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleItemEnum (roleUUID, roleName, roleMoney, renameCard) "
                              "VALUES (:roleUUID, :roleName, :roleMoney, :renameCard)";
        query.prepare(insertQuery);
        query.bindValue(":roleUUID", "UUID");
        query.bindValue(":roleName", "GM姜子牙");
        query.bindValue(":roleMoney", 100);
        query.bindValue(":renameCard", 2);
        if (!query.exec())
        {
            qDebug() << "插入初始值时出错:" << query.lastError().text();
            return false;
        }
    }

    // 检查 RoleCoefficient 表是否存在 角色各项系数
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleCoefficient'";
    if (!query.exec(queryString))
    {
        qDebug() << "执行查询 RoleCoefficient 时出错:" << query.lastError().text();
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
            qDebug() << "创建表时出错:" << query.lastError().text();
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
            qDebug() << "插入初始值时出错:" << query.lastError().text();
            return false;
        }
    }
    return true;
}

QString DataManage::GetTableToInfo(QString table_name, QString column_name)
{
    QString result = "";
    if(!database_.isOpen())
    {
        qDebug() << "数据库打开失败";
        return result;
    }
    else
    {
        QSqlQuery query;
        QString queryString = QString("SELECT %1 FROM %2").arg(column_name, table_name);
        if (!query.exec(queryString))
        {
            qDebug() << queryString;
            qDebug() << "执行查询时出错:" << query.lastError().text();
            // database_.close();
        }
        else
        {
            if (query.next())
            {
                qDebug() << table_name << " 查询数据为：" << column_name << " ：" << query.value(0).toString();
                // database_.close();
                result = query.value(0).toString();
            }
        }
        // database_.close();
        return result;
    }
}

void DataManage::DatabaseClose()
{
    // database_.close();
}

void DataManage::SlotSaveRoleInfoToDatabase(QJsonObject role_data)
{
    is_SaveRoleInfo = true;
    this->role_data = role_data;
    start();
}

void DataManage::SlotSaveRoleItemToDatabase(QJsonObject role_item_data)
{
    is_SaveRoleItem = true;
    this->role_item_data = role_item_data;
    start();
}

void DataManage::SlotSaveRoleCoefficientToDatabase(QJsonObject RC_data)
{
    is_SaveRoleCoefficient = true;
    this->RC_data = RC_data;
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
    if(database_.isOpen())
    {
        QString roleName = role_data.value("roleName").toString();

        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM RoleInfo WHERE roleName = :roleName");
        query.bindValue(":roleName", roleName);

        if (query.exec() && query.next())
        {
            int rowCount = query.value(0).toInt();
            if (rowCount > 0)
            {
                // 执行更新操作
                QString updateQuery = "UPDATE RoleInfo SET roleLife = :roleLife, rolePrestige = :rolePrestige, roleLv = :roleLv, roleCurExp = :roleCurExp,"
                                      "roleExp = :roleExp, roleAgg = :roleAgg, roleDef = :roleDef, roleHp = :roleHp WHERE roleName = :roleName";
                query.prepare(updateQuery);
            }
            else
            {
                // 执行插入操作
                QString insertQuery = "INSERT INTO RoleInfo (roleName, roleLife, rolePrestige, roleCultivation, roleExp, roleAgg, roleDef, roleHp, roleCurExp) "
                                      "VALUES (:roleName, :roleLife, :rolePrestige, :roleCultivation, :roleExp, :roleAgg, :roleDef, :roleHp, :roleCurExp)";
                query.prepare(insertQuery);
            }

            query.bindValue(":roleName", roleName);
            query.bindValue(":roleLife", role_data.value("roleLife").toInt());
            query.bindValue(":rolePrestige", role_data.value("rolePrestige").toInt());
            query.bindValue(":roleLv", role_data.value("roleLv").toInt());
            query.bindValue(":roleExp", role_data.value("roleExp").toInt());
            query.bindValue(":roleAgg", role_data.value("roleAgg").toInt());
            query.bindValue(":roleDef", role_data.value("roleDef").toInt());
            query.bindValue(":roleHp", role_data.value("roleHp").toInt());
            query.bindValue(":roleCurExp", role_data.value("roleCurExp").toInt());
            if (!query.exec())
            {
                qDebug() << "保存数据时出错:" << query.lastError().text();
                // database_.close();
                return;
            }
        }
    }
    else
    {
        qDebug() << "数据库未打开";
    }
}

void DataManage::WriteRoleItemsToLocalDatabase()
{
    if(database_.isOpen())
    {
        QString roleName = role_item_data.value("roleName").toString();

        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM RoleItemEnum WHERE roleName = :roleName");
        query.bindValue(":roleName", roleName);

        if (query.exec() && query.next())
        {
            int rowCount = query.value(0).toInt();
            if (rowCount > 0)
            {
                // 执行更新操作
                QString updateQuery = "UPDATE RoleItemEnum SET roleMoney = :roleMoney, renameCard = :renameCard WHERE roleName = :roleName";
                query.prepare(updateQuery);
            }
            else
            {
                // 执行插入操作
                QString insertQuery = "INSERT INTO RoleItemEnum (roleName, roleMoney, renameCard) "
                                      "VALUES (:roleName, :roleMoney, :renameCard)";
                query.prepare(insertQuery);
            }

            query.bindValue(":roleName", roleName);
            query.bindValue(":roleMoney", role_item_data.value("roleMoney").toInt());
            query.bindValue(":renameCard", role_item_data.value("renameCard").toInt());
            if (!query.exec())
            {
                qDebug() << "保存数据时出错:" << query.lastError().text();
                return;
            }
        }
    }
    else
    {
        qDebug() << "数据库未打开";
    }
}

void DataManage::WriteRoleCoefficientToLocalDatabase()
{
    if(database_.isOpen())
    {
        QString roleName = RC_data.value("roleName").toString();

        QSqlQuery query;
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
            query.bindValue(":RCLife", RC_data.value("RCLife").toInt());
            query.bindValue(":RCBasicEvent", RC_data.value("RCBasicEvent").toInt());
            query.bindValue(":RCAttEvent", RC_data.value("RCAttEvent").toInt());
            query.bindValue(":RCSurviveDisaster", RC_data.value("RCSurviveDisaster").toInt());
            query.bindValue(":RCPrestigeEvent", RC_data.value("RCPrestigeEvent").toInt());
            query.bindValue(":RCSpecialEvent", RC_data.value("RCSpecialEvent").toInt());
            query.bindValue(":roleAptitude", RC_data.value("roleAptitude").toInt());
            if (!query.exec())
            {
                qDebug() << "保存数据时出错:" << query.lastError().text();
                return;
            }
        }
    }
    else
    {
        qDebug() << "数据库未打开";
    }
}

void DataManage::run()
{
    QMutexLocker locker(&mutex);
    InitRemoteData();
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
#elif DATABASE_TYPE == 2
#endif
}
