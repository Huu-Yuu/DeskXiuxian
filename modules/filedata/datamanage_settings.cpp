#include "data_manage.h"

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
            qDebug() << "配置文件创建失败";
        }
    }
    file_setting_ = new QSettings(configFilePath, QSettings::IniFormat);
    file_setting_->setValue("123456",456456);
    file_setting_->setIniCodec("UTF-8");
}

void DataManage::SetGameConfigInfo()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyy-MM-dd hh:mm:ss");

    file_setting_->setPath(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::applicationDirPath() + "/config.ini");
    file_setting_->setValue("Date/LastGameDate", formattedTime);
    file_setting_->sync();
    qDebug() << "写入最后运行时间：" << formattedTime;
}

void DataManage::SetUserInfoToConfig(QString user_name, QString pass_word, QString email)
{
    file_setting_->setValue("UserInfo/UserName", user_name);
    file_setting_->setValue("UserInfo/PassWord", pass_word);
    file_setting_->setValue("UserInfo/Email", email);
    file_setting_->sync();
    qDebug() << "记录用户信息到配置文件";
}

QString DataManage::GetLastGameTime()
{
    return file_setting_->value("Date/LastGameDate", "").toString();
}

QString DataManage::GetSettingUserName()
{
    return file_setting_->value("UserInfo/UserName", "").toString();
}

QString DataManage::GetSettingPassWord()
{
    return file_setting_->value("UserInfo/PassWord", "").toString();
}
