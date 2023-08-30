#ifndef PUBLICFUNC_H
#define PUBLICFUNC_H

#include <QObject>
#include <QNetworkInterface>
#include "public/error_code.h"

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
};

#endif // PUBLICFUNC_H
