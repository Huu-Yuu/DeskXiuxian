#include "datamanage.h"

QMutex DataManage::mutex;  // 初始化互斥锁对象
DataManage* DataManage::instance = nullptr;  // 初始化单例对象指针
DataManage* DataManage::GetInstance()
{
    if (instance == nullptr)
    {
        QMutexLocker locker(&mutex);  // 加锁
        if (instance == nullptr) {
            instance = new DataManage();
        }
    }
    return instance;
}

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
    file_setting_ = new QSettings(configFilePath,QSettings::IniFormat);

    file_setting_->setIniCodec("UTF-8");

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

DataManage::~DataManage()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyy-MM-dd hh:mm:ss");

    file_setting_->setPath(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::applicationDirPath() + "/config.ini");
    file_setting_->setValue("Date/LastGameDate", formattedTime);
    file_setting_->sync();
    qDebug() << "写入最后运行时间："<< formattedTime;
    if(file_setting_ != NULL)
    {
        delete file_setting_;
        file_setting_ = NULL;
    }
}

void DataManage::OpenDatabase(QString path)
{
    // 打开现有数据库连接
    database_ = QSqlDatabase::addDatabase("QSQLITE");
    database_.setDatabaseName(path);
    database_.exec("PRAGMA encoding = \"UTF-8\";");

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
            qDebug()<<"检查表单时出现错误";
        };
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
        qDebug() << "创建数据库失败:" << database_.lastError().text();
    }
    else
    {
        if(!CheckTablesExist()) //检查并创建表单
        {
            qDebug()<<"创建数据库时，创建表单出现错误";
        };
    }
    database_.close();

    // 在此处可以执行数据库表的初始化操作
    // ...
}

bool DataManage::CheckTablesExist()
{
    if(!database_.open())
    {
        qDebug() << "数据库打开失败";
        return false;
    }
    QSqlQuery query(database_);
    QString queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleInfo'";
    if (!query.exec(queryString))
    {
        qDebug() << "执行查询 RoleInfo 时出错:" << query.lastError().text();
        return false;
    }
    // 如果 RoleInfo 表不存在，则创建表
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleInfo ("
                                   "roleName TEXT,"
                                   "roleLife INTEGER,"
                                   "rolePrestige INTEGER,"
                                   "roleCultivation TEXT,"
                                   "roleExp INTEGER,"
                                   "roleAgg INTEGER,"
                                   "roleDef INTEGER,"
                                   "roleHp INTEGER"
                                   ")";
        query.prepare(createTableQuery);
        if (!query.exec(createTableQuery))
        {
            qDebug() << "创建表时出错:" << query.lastError().text();
            return false;
        }
        // 插入初始值
        QString insertQuery = "INSERT INTO RoleInfo (roleName, roleLife, rolePrestige, roleCultivation, roleExp, roleAgg, roleDef, roleHp) "
                              "VALUES (:roleName, :roleLife, :rolePrestige, :roleCultivation, :roleExp, :roleAgg, :roleDef, :roleHp)";
        query.prepare(insertQuery);
        query.bindValue(":roleName", "GM姜子牙");
        query.bindValue(":roleLife", 80);
        query.bindValue(":rolePrestige", 989);
        query.bindValue(":roleCultivation", "凡人");
        query.bindValue(":roleExp", 8989);
        query.bindValue(":roleAgg", 99);
        query.bindValue(":roleDef", 40);
        query.bindValue(":roleHp", 20);

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
        QString insertQuery = "INSERT INTO RoleAtt (attMetal, attWood, attWater, attFire, attEarth) "
                              "VALUES (:attMetal, :attWood, :attWater, :attFire, :attEarth)";
        query.prepare(insertQuery);
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
                                   "equipWeapon TEXT,"
                                   "equipMagic TEXT,"
                                   "equipHelmet TEXT,"
                                   "equipClothing TEXT,"
                                   "equipBritches TEXT,"
                                   "equipShoe TEXT,"
                                   "equipJewelry TEXT"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            qDebug() << "创建表时出错:" << query.lastError().text();
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleEquip (equipWeapon, equipMagic, equipHelmet, equipClothing, equipBritches, equipShoe, equipJewelry) "
                              "VALUES (:equipWeapon, :equipMagic, :equipHelmet, :equipClothing, :equipBritches, :equipShoe, :equipJewelry)";
        query.prepare(insertQuery);
        query.bindValue(":equipWeapon", "打神鞭");
        query.bindValue(":equipMagic", "封神榜");
        query.bindValue(":equipHelmet", "洪荒盔");
        query.bindValue(":equipClothing", "洪荒甲");
        query.bindValue(":equipBritches", "洪荒腰带");
        query.bindValue(":equipShoe", "洪荒靴");
        query.bindValue(":equipJewelry", "乾坤戒");
        if (!query.exec())
        {
            qDebug() << "插入初始值时出错:" << query.lastError().text();
            return false;
        }
    }

    // 检查 RoleProp 表是否存在
    queryString = "SELECT name FROM sqlite_master WHERE type='table' AND name='RoleProp'";
    if (!query.exec(queryString))
    {
        qDebug() << "执行查询 RoleProp 时出错:" << query.lastError().text();
        return false;
    }

    // 如果 RoleProp 表不存在，则创建表并初始化字段值
    if (!query.next())
    {
        QString createTableQuery = "CREATE TABLE RoleProp ("
                                   "RenamCard INTEGER"
                                   ")";
        if (!query.exec(createTableQuery))
        {
            qDebug() << "创建表时出错:" << query.lastError().text();
            return false;
        }

        // 初始化字段值
        QString insertQuery = "INSERT INTO RoleProp (RenamCard) "
                              "VALUES (:RenamCard)";
        query.prepare(insertQuery);
        query.bindValue(":RenamCard", 2);
        if (!query.exec())
        {
            qDebug() << "插入初始值时出错:" << query.lastError().text();
            return false;
        }
    }
    database_.close();
    return true;
}

QString DataManage::GetTableToInfo(QString table_name, QString column_name)
{
    if(!database_.open())
    {
        qDebug() << "数据库打开失败";
        return QString();
    }
    else
    {
        QSqlQuery query(database_);
        QString queryString = QString("SELECT %1 FROM %2").arg(column_name,table_name);
        if (!query.exec(queryString))
        {
            qDebug() << queryString;
            qDebug() << "执行查询时出错:" << query.lastError().text();
            return QString();
        }
        if (query.next())
        {
            qDebug() << table_name << " 查询数据为：" << column_name << " ："<< query.value(0).toString();
            return query.value(0).toString();
        }
        return QString();
    }
}

QString DataManage::GetLastGameTime()
{
    return file_setting_->value("Date/LastGameDate").toString();
}

void DataManage::DatabaseClose()
{
    database_.close();
}
