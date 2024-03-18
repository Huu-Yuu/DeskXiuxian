#ifndef PUBLICFUNC_H
#define PUBLICFUNC_H

#include <QObject>
#include <QNetworkInterface>
#include "error_code.h"
#include "public_type.h"

/**
 * @brief 公共函数类
 */
class PublicFunc : public QObject
{
public:

    /**
     * @brief 计算校验和
     * @param data：要计算校验和的数据
     * @param len：要计算校验和的数据个数
     * @return 校验和
     * @note 1.校验和也叫和校验，是将各数据直接求和后去除溢出部分剩下的数据。
     *       2.输入数据不用包括校验位和加上校验长度
     */
    static uchar CalculateSum(const uchar* data, const int len);

    /**
     * @brief 获取日期字符串
     * @param ouput_data：日期数据
     * @param ouput_len：日期数据长度
     * @return NO_ERROR
     * @note 1.返回数值小于64字节。格式：”%Y-%m-%d %H:%M:%S 星期？“
     *       2.使用Qt和C++直接用QDateTime获取日期字符串
     */
    static int GetDataString(char* ouput_data, size_t* ouput_size);

    /**
     * @brief 获取本地IP地址
     */
    static QString GetLocalIpAddress();

    static ItemType ConvertItemType(RoleItemEnum item_enum);  ///< 物品索引计算物品类型
    static RoleEquipAreaEnum ConvertEquipArea(RoleItemEnum item_enum);  ///< 物品索引计算装备部位
    static QString ConvertEquipAreaStr(RoleEquipAreaEnum area_enum);  ///< 装备部位转DB字符串
    static QString GetCultivationName(int cur_lv);  ///< 获取等级名称

    // 打包请求数据
    static QJsonObject PackageRequest(const QString& type, const QJsonObject& data, QString id,
                                      const QString& dest, const QString& ori);

    static QJsonObject PackageRequest_timeInt(const QString& type, const QJsonObject& data,
                                              QString id, const QString& dest, const QString& ori);

    static QJsonObject PackageResponse_timeInt(const QString& type, const QString& id, int status,
                                               const QJsonObject& data, const QJsonObject& error, const QString& dest, QString ori);

    // 打包应答数据
    static QJsonObject PackageResponse(const QString& type, const QString& id, int status, const QJsonObject& data,
                                       const QJsonObject& error, const QString& dest, QString ori);
};

#endif // PUBLICFUNC_H
