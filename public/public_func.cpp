#include "public_func.h"

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
