#include "business/db_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

DBManage::DBManage() {
    m_module_name = module_name::data;
    m_service_ = DataService::getInstance();

    connect(m_service_, &DataService::SignalActionRequest, this, &DBManage::SignalActionRequest);
    connect(m_service_, &DataService::SignalActionResponse, this, &DBManage::SignalActionResponse);
    connect(m_service_, &DataService::SignalPubTopic, this, &DBManage::SignalPubTopic);

    map_function_request_[mainCmd::InitLocalRoleInfo] = &DBManage::Do_Request_InitLocalRoleInfo;
    map_function_request_[mainCmd::InitRemoteRoleInfo] = &DBManage::Do_Request_InitRemoteRoleInfo;
    map_function_request_[mainCmd::AutomaticLogin] = &DBManage::Do_Request_AutomaticLogin;
    map_function_request_[dbCmd::CheckLoginFist] = &DBManage::Do_Request_CheckLoginFist;
    map_function_request_[dbCmd::CheckRoleNameIsOk] = &DBManage::Do_Request_CheckRoleNameIsOk;
    map_function_request_[dbCmd::LoginVerification] = &DBManage::Do_Request_LoginVerification;
    map_function_request_[dbCmd::SetUserInfoToConfig] = &DBManage::Do_Request_SetUserInfoToConfig;
    map_function_request_[dbCmd::AccountRegistration] = &DBManage::Do_Request_AccountRegistration;
    map_function_request_[dbCmd::UpdateLastLoginTime] = &DBManage::Do_Request_UpdateLastLoginTime;
    map_function_request_[roleCmd::ModifyRoleName] = &DBManage::Do_Request_ModifyRoleName;

    map_function_topic_[dbCmd::SaveRoleEquip] = &DBManage::Do_Topic_SaveRoleEquip;
    map_function_topic_[dbCmd::SaveRoleInfo] = &DBManage::Do_Topic_SaveRoleInfo;
    map_function_topic_[dbCmd::SaveCoefficient] = &DBManage::Do_Topic_SaveCoefficient;
    map_function_topic_[dbCmd::SaveRoleItem] = &DBManage::Do_Topic_SaveRoleItem;
}

int DBManage::Init()
{
    QStringList db_topics = QStringList{dbCmd::SaveRoleEquip, dbCmd::SaveRoleItem, dbCmd::SaveRoleInfo, dbCmd::SaveCoefficient};
    QStringList subscribe_topics;
    subscribe_topics += db_topics;
    LOG_INFO(kDataManage, QString("发送订阅主动上报消息：%1").arg(subscribe_topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, subscribe_topics);
}

DBManage::~DBManage()
{

}

void DBManage::SlotActionResponse(const QJsonObject& response_data)
{
    LOG_INFO(kRoleManage, QString("收到外部应答：%1").arg(QJsonDocument(response_data).toJson(QJsonDocument::Compact).data()));
    QString type = response_data.value("type").toString();
    if(map_function_response_.keys().contains(type))
    {
        (this->*map_function_response_[type])(response_data);
    }
}

void DBManage::SlotActionRequest(const QJsonObject& request_data)
{
    LOG_INFO(kRoleManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(map_function_request_.keys().contains(type))
    {
        (this->*map_function_request_[type])(request_data);
    }
}

void DBManage::SlotPubTopic(const QJsonObject& topic_data)
{
    LOG_INFO(kDataManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    QString type = topic_data.value("type").toString();
    if(map_function_topic_.keys().contains(type))
    {
        (this->*map_function_topic_[type])(topic_data);
    }
}

void DBManage::Do_Request_InitLocalRoleInfo(const QJsonObject &request_data)
{
    Q_UNUSED(request_data);
    m_service_->InitLocalRoleInfo();
}

void DBManage::Do_Request_InitRemoteRoleInfo(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_service_->InitRemoteRoleInfo();
}

void DBManage::Do_Request_CheckLoginFist(const QJsonObject& request_data)
{
    int result = m_service_->CheckUserLogginIsFist();   ///< 0-非首次登录  1-首次登录
    QJsonObject data_obj;
    data_obj.insert("result", result);
    emit SignalActionResponse(PublicFunc::PackageResponse(dbCmd::CheckLoginFist,
                                                          request_data.value("id").toString(),
                                                          0,
                                                          data_obj,
                                                          QJsonObject(),
                                                          request_data.value("ori").toString(),
                                                          module_name::data));
}

void DBManage::Do_Request_AutomaticLogin(const QJsonObject& request_data)
{
    int result = m_service_->AutomaticLogin();
    QJsonObject data_obj;
    data_obj.insert("result", result);
    emit SignalActionResponse(PublicFunc::PackageResponse(mainCmd::AutomaticLogin,
                                                          request_data.value("id").toString(),
                                                          0,
                                                          data_obj,
                                                          QJsonObject(),
                                                          request_data.value("ori").toString(),
                                                          module_name::data));
}

void DBManage::Do_Request_ModifyRoleName(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    int result = m_service_->ModifyRoleName(data.value("name").toString());
    QJsonObject data_obj;
    data_obj.insert("result", result);
    emit SignalActionResponse(PublicFunc::PackageResponse(roleCmd::ModifyRoleName,
                                                          request_data.value("id").toString(),
                                                          0,
                                                          data_obj,
                                                          QJsonObject(),
                                                          request_data.value("ori").toString(),
                                                          module_name::data));
}

void DBManage::Do_Request_CheckRoleNameIsOk(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    int result = m_service_->CheckRoleNameIsOk(data.value("name").toString());
    QJsonObject data_obj;
    data_obj.insert("result", result);
    emit SignalActionResponse(PublicFunc::PackageResponse(dbCmd::CheckRoleNameIsOk,
                                                          request_data.value("id").toString(),
                                                          0,
                                                          data_obj,
                                                          QJsonObject(),
                                                          request_data.value("ori").toString(),
                                                          module_name::data));
}

void DBManage::Do_Request_LoginVerification(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    QString user_name, pass_word;
    user_name = data.value("user_name").toString();
    pass_word = data.value("pass_word").toString();
    int result = m_service_->LoginVerification(user_name, pass_word);
    QJsonObject data_obj;
    data_obj.insert("result", result);
    emit SignalActionResponse(PublicFunc::PackageResponse(dbCmd::LoginVerification,
                                                          request_data.value("id").toString(),
                                                          0,
                                                          data_obj,
                                                          QJsonObject(),
                                                          request_data.value("ori").toString(),
                                                          module_name::data));
}

void DBManage::Do_Request_SetUserInfoToConfig(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    QString user_name, pass_word, e_mail;
    user_name = data.value("user_name").toString();
    pass_word = data.value("pass_word").toString();
    e_mail = data.value("e_mail").toString();
    m_service_->SetUserInfoToConfig(user_name, pass_word, e_mail);
}

void DBManage::Do_Request_AccountRegistration(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    QString user_name, pass_word, e_mail;
    user_name = data.value("user_name").toString();
    pass_word = data.value("pass_word").toString();
    e_mail = data.value("e_mail").toString();
    int result = m_service_->AccountRegistration(user_name, pass_word, e_mail);
    QJsonObject data_obj;
    data_obj.insert("result", result);
    emit SignalActionResponse(PublicFunc::PackageResponse(dbCmd::AccountRegistration,
                                                          request_data.value("id").toString(),
                                                          0,
                                                          data_obj,
                                                          QJsonObject(),
                                                          request_data.value("ori").toString(),
                                                          module_name::data));
}

void DBManage::Do_Request_UpdateLastLoginTime(const QJsonObject& request_data)
{
    m_service_->UpdateLastLoginTime();
    QJsonObject data_obj;
    data_obj.insert("result", 1);
    emit SignalActionResponse(PublicFunc::PackageResponse(dbCmd::UpdateLastLoginTime,
                                                          request_data.value("id").toString(),
                                                          0,
                                                          data_obj,
                                                          QJsonObject(),
                                                          request_data.value("ori").toString(),
                                                          module_name::data));
}

void DBManage::Do_Topic_SaveRoleEquip(const QJsonObject& topic_data)
{
    QJsonObject data = topic_data.value("data").toObject();
    m_service_->SlotSaveRoleEquipToDatabase(data);
}

void DBManage::Do_Topic_SaveRoleInfo(const QJsonObject& topic_data)
{
    QJsonObject data = topic_data.value("data").toObject();
    m_service_->SlotSaveRoleInfoToDatabase(data);
}

void DBManage::Do_Topic_SaveCoefficient(const QJsonObject& topic_data)
{
    QJsonObject data = topic_data.value("data").toObject();
    m_service_->SlotSaveRoleCoefficientToDatabase(data);
}

void DBManage::Do_Topic_SaveRoleItem(const QJsonObject& topic_data)
{
    QJsonObject data = topic_data.value("data").toObject();
    int opt = data.value("prop_opt").toInt();
    data.remove("prop_opt");
    m_service_->GetPropOpt(opt);
    m_service_->SlotSaveRoleItemToDatabase(data);
}
