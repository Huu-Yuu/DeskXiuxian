#include <QJsonObject>
#include <utility>
#include "public_func.h"
#include "QDateTime"
#include "QUuid"
#include "public_macro.h"
#include "public_declare.h"
#include <QFile>

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
            LOG_DEBUG(kMainCtrl, QString("不存在此类型:%1，强制转换为道具类型").arg(type_num));
            return kItemProp;
    }
}

QString PublicFunc::ConvertItemEnumToDBStr(RoleItemEnum item_enum)
{
    ItemType item_type = ConvertItemType(item_enum);
    if(item_type != kItemEquip)
    {
        return QString("item_%1").arg(QString::number(item_enum));
    }
    else
    {
        LOG_DEBUG(kMainCtrl, QString("不能将装备类型转换为数据库类名：%1").arg(QString::number(item_enum)));
        return "";
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
            return kJewelrArea;
        case 8:
            return kMountArea;
        case 9:
            return kTitleArea;
        default:
            LOG_DEBUG(kMainCtrl, QString("不存在此类型部位%1").arg(type_num));
            return kOther;
    }
}

QString PublicFunc::ConvertEquipAreaToDBStr(RoleEquipAreaEnum area_enum) {
    QString area_str;
    switch (area_enum)
    {
        case kOther:
            LOG_DEBUG(kMainCtrl, "不存在此部位");
            break;
        case kWeaponArea:
            area_str = "equip_weapon";
            break;
        case kMagicArea:
            area_str = "equip_magic";
            break;
        case kHelmetArea:
            area_str = "equip_helmet";
            break;
        case kClothingArea:
            area_str = "equip_clothing";
            break;
        case kBritchesArea:
            area_str = "equip_britches";
            break;
        case kShoeArea:
            area_str = "equip_shoe";
            break;
        case kJewelrArea:
            area_str = "equip_jewelry";
            break;
        case kMountArea:
            area_str = "equip_mount";
            break;
        case kTitleArea:
            area_str = "equip_title";
            break;
    }
    return area_str;
}

QString PublicFunc::GetCultivationName(int cur_lv) {
    CultivationStage lv = (CultivationStage)cur_lv;
    switch (lv)
    {
        case FANREN:
            return "凡人";
        case LIANQI:
            return "练气";
        case ZHUJI:
            return "筑基";
        case JIEDAN:
            return "结丹";
        case YUANYING:
            return "元婴";
        case HUASHEN:
            return "化神";
        case HETI:
            return "合体";
        case DACHENG:
            return "大乘";
        case WUDAO:
            return "悟道";
        case YUHUA:
            return "羽化";
        case XIAN:
            return "仙";
        case MAXLV:
            return "最高等级标记";
    }
    return "";
}

QString PublicFunc::ConvertBaseAttEnumToDBStr(RoleBaseAttEnum arr_enum) {
    switch (arr_enum) {
        case kRoleNameAtt:
            return "role_name";
        case kRoleLifeAtt:
            return "role_life";
        case kRolePrestigeAtt:
            return "role_prestige";
        case kRoleLvAtt:
            return "role_lv";
        case kRoleExpAtt:
            return "role_cur_exp";
        case kRoleAggAtt:
            return "role_att";
        case kRoleDefAtt:
            return "role_def";
        case kRoleHpAtt:
            return "role_hp";
        case kRoleMaxLifeAtt:
            return "role_max_life";
        case kRoleMaxExpAtt:
            return "role_exp";
    }
}

