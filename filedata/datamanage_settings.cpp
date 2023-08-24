#include "filedata/datamanage.h"

void DataManage::InitSettingFile()
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
    file_setting_ = new QSettings(configFilePath, QSettings::IniFormat);

    file_setting_->setIniCodec("UTF-8");
}

QString DataManage::GetLastGameTime()
{
    return file_setting_->value("Date/LastGameDate").toString();
}

QString DataManage::GetUserName()
{
    return file_setting_->value("UserInfo/UserName").toString();
}

QString DataManage::GetPassWord()
{
    return file_setting_->value("UserInfo/PassWord").toString();
}
