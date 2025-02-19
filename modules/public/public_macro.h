#ifndef PUBLIC_MACRO_H
#define PUBLIC_MACRO_H

// 调试信息输出开关
#define DEBUG_MODE_SWITCH       1

#define GAME_VISION             "v0.5.2 重构版"

    // 数据库类型    0-远程数据库 1-本地数据库 2-服务器
#define DATABASE_TYPE           1
// 远程数据库链接名
#define REMOTE_DB_LINKNAME      "GAMEDATA_REMOTE"
// 本地数据库链接名
#define LOCAL_DB_LINKNAME      "GAMEDATA_LOCCAL"

// 远程数据库地址
#define REMOTE_DB_ADDRESS       "mysql.sqlpub.com"

// 远程数据库端口号
#define REMOTE_DB_PORT          3306

// 远程数据库用户名
#define REMOTE_DB_USERNAME      "xiuxian"

// 远程数据库密码
#define REMOTE_DB_PASSWORD      "ef8ead2a1a2704c4"

// 远程数据库密码
#define LOCAL_DB_PASSWORD       "xiuxian666"

// 本地数据库名称
#define REMOTE_DB_NAME          "desk_xiuxian"

// 网络通信IP地址
#define MAIN_SERVER_IP          "127.0.0.1"

// 网络通信端口
#define MAIN_SERVER_PORT        12306

// 调试打印
#if DEBUG_MODE_SWITCH == 1
// 调试打印
#define LOG_INFO(logger, msg) \
    do { \
        QString logMsg = QString("[%1] %2:%3 - %4").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(__FUNCTION__).arg(__LINE__).arg(msg); \
        qDebug() << logMsg; \
        QString logFileName = "../log/" + QDateTime::currentDateTime().toString("yyyyMMdd") + "_" + logger + ".log"; \
        QFile file(logFileName); \
        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) { \
            QTextStream stream(&file); \
            stream << logMsg << endl; \
            file.close(); \
        } \
    } while (0)
#else
#define LOG_INFO(msg) do {} while (0)
#endif

#endif // PUBLIC_MACRO_H
