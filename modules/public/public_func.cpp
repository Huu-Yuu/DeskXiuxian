#include <QJsonObject>
#include <utility>
#include "public_func.h"
#include "QDateTime"
#include "QUuid"
#include "public_macro.h"

uchar PublicFunc::CalculateSum(const uchar* data, const int len)
{
    uchar sum = 0;
    for (int i = 0; i < len; ++i)
    {
        sum += data[i];
    }
    return sum;
}

int PublicFunc::GetDataString(char* ouput_data, size_t* ouput_size)
{
    char buf[64] = {0};
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S ", timeinfo);
    //strftime(buf, sizeof(buf), "%F %X ", timeinfo);
    sprintf(ouput_data, "%s", buf);
    strftime(buf, sizeof(buf), "%a", timeinfo);
    if ((strncmp(buf, "Mon", 3) == 0) || (strcmp(buf, "一") == 0))
    {
        strcat(ouput_data, "星期一");
    }
    else if ((strncmp(buf, "Tues", 4) == 0) || (strcmp(buf, "二") == 0))
    {
        strcat(ouput_data, "星期二");
    }
    else if ((strncmp(buf, "Wed", 3) == 0) || (strcmp(buf, "三") == 0))
    {
        strcat(ouput_data, "星期三");
    }
    else if ((strncmp(buf, "Thur", 3) == 0) || (strcmp(buf, "四") == 0))
    {
        strcat(ouput_data, "星期四");
    }
    else if ((strncmp(buf, "Fri", 3) == 0) || (strcmp(buf, "五") == 0))
    {
        strcat(ouput_data, "星期五");
    }
    else if ((strncmp(buf, "Sat", 3) == 0) || (strcmp(buf, "六") == 0))
    {
        strcat(ouput_data, "星期六");
    }
    else if ((strncmp(buf, "Sun", 3) == 0) || (strcmp(buf, "日") == 0))
    {
        strcat(ouput_data, "星期日");
    }
    else
    {
        strcat(ouput_data, "星期?");
    }
    *ouput_size = strlen(ouput_data);
    return NO_ERROR;
}

QString PublicFunc::GetLocalIpAddress()
{
    QString ipAddress;

    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interface, interfaceList)
    {
        // 过滤回环接口和无效接口
        if (interface.flags().testFlag(QNetworkInterface::IsLoopBack) || !interface.isValid())
            continue;

        QList<QNetworkAddressEntry> addressEntryList = interface.addressEntries();
        foreach (QNetworkAddressEntry addressEntry, addressEntryList)
        {
            // 获取 IPv4 地址
            if (addressEntry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                ipAddress = addressEntry.ip().toString();
                break;
            }
        }
    }
    return ipAddress;
}

QJsonObject PublicFunc::PackageRequest(const QString& type, const QJsonObject &data, QString id,
                                       const QString& dest, const QString& ori) {
    QJsonObject out_obj = PackageRequest_timeInt(type, data, std::move(id), dest, ori);
    out_obj.insert("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    return out_obj;
}

QJsonObject PublicFunc::PackageRequest_timeInt(const QString& type, const QJsonObject &data, QString id,
                                               const QString& dest, const QString& ori) {
    QJsonObject out_obj = QJsonObject();
    if(!ori.isEmpty())
        out_obj.insert("ori", ori);
    else
        out_obj.insert("ori", "Game");
    out_obj.insert("dest", dest);
    if(id.isEmpty())
    {
        id = QUuid::createUuid().toString();
    }
    out_obj.insert("id", id);
    out_obj.insert("type", type);
    out_obj.insert("time", QDateTime::currentDateTime().toSecsSinceEpoch());
    out_obj.insert("data", data);
    return out_obj;
}

QJsonObject PublicFunc::PackageResponse_timeInt(const QString& type, const QString& id, int status,
                                                const QJsonObject& data, const QJsonObject& error, const QString& dest, QString ori)
{
    QJsonObject out_obj = QJsonObject();
    if(!ori.isEmpty())
        out_obj.insert("ori", ori);
    else
        out_obj.insert("ori", "robot");
    out_obj.insert("dest", dest);
    out_obj.insert("id", id);
    out_obj.insert("type", type);
    out_obj.insert("status", status);
    out_obj.insert("time", QDateTime::currentDateTime().toSecsSinceEpoch());
    if(status != 0)
    {
        out_obj.insert("error", error);
    }
    out_obj.insert("data", data);
    return out_obj;

}

QJsonObject PublicFunc::PackageResponse(const QString& type, const QString& id, int status,
                                        const QJsonObject& data, const QJsonObject& error, const QString& dest, QString ori)
{
    QJsonObject out_obj = PackageResponse_timeInt(type, id, status, data, error, dest, ori);
    out_obj.insert("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    return out_obj;

}

ItemType PublicFunc::ConvertItemType(RoleItemEnum item_enum) {
    QString enum_type = QString::number(item_enum);
    QString type_num = enum_type.left(1);
    switch (type_num.toInt()) {
        case 1:
            return kItemProp;
            break;
        case 2:
            return kItemMaterial;
            break;
        case 3:
            return kItemSpecial;
            break;
        case 4:
            return kItemEquip;
            break;
        default:
            LOG_DEBUG(QString("不存在此类型:%1，强制转换为道具类型").arg(type_num));
            return kItemProp;
    }
}

RoleEquipAreaEnum PublicFunc::ConvertEquipArea(RoleItemEnum item_enum) {
    QString enum_type = QString::number(item_enum);
    QString type_num = enum_type.mid(1, 1); // 提取第二位数字
    switch (type_num.toInt()) {
        case 1:
            return kWeaponArea;
        case 2:
            return kMagicArea;
        case 3:
            return kHelmetArea;
        case 4:
            return kClothingArea;
        case 5:
            return kBritchesArea;
        case 6:
            return kShoeArea;
        case 7:
            return kJewelrtArea;
        case 8:
            return kMountArea;
        case 9:
            return kTitleArea;
        default:
            LOG_DEBUG(QString("不存在此类型部位%1").arg(type_num));
            return kOther;
    }
}
