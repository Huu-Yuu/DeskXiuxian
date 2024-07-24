#include "business/role_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

RoleManage::RoleManage() {
    m_module_name = module_name::role;
    m_player_ = RolePlayer::getInstance();

    connect(m_player_, &RolePlayer::SignalActionRequest, this, &RoleManage::SignalActionRequest);
    connect(m_player_, &RolePlayer::SignalActionResponse, this, &RoleManage::SignalActionResponse);
    connect(m_player_, &RolePlayer::SignalPubTopic, this, &RoleManage::SignalPubTopic);

    map_function_request_[mainCmd::InitLocalRoleInfo] = &RoleManage::Do_Request_InitLocalRoleInfo;
    map_function_request_[uiCmd::UpgradeLevel] = &RoleManage::Do_Request_UpgradeLevel;
    map_function_request_[ProgressCmd::CyclicLifeUpdate] = &RoleManage::Do_Request_CyclicLifeUpdate;
    map_function_request_[ProgressCmd::CyclicCultivation] = &RoleManage::Do_Request_CyclicCultivation;
    map_function_request_[ProgressCmd::CyclicEnhanceAtt] = &RoleManage::Do_Request_CyclicEnhanceAtt;
    map_function_request_[roleCmd::ModifyRoleName] = &RoleManage::Do_Request_ModifyRoleName;
    map_function_request_[itemCmd::IncreModRoleBaseAtt] = &RoleManage::Do_Request_IncreModRoleBaseAtt;

    map_function_topic_[dbCmd::SaveRoleEquip] = &RoleManage::Do_Topic_SaveRoleEquip;
    map_function_topic_[dbCmd::SaveRoleItem] = &RoleManage::Do_Topic_SaveRoleItem;
    map_function_topic_[uiCmd::StartFishing] = &RoleManage::Do_Topic_StartFishing;
}

int RoleManage::Init()
{
    QStringList db_topics = QStringList{dbCmd::SaveRoleEquip, dbCmd::SaveRoleItem};
    QStringList ui_topics = QStringList{uiCmd::StartFishing};
    QStringList subscribe_topics;
    subscribe_topics += db_topics;
    subscribe_topics += ui_topics;
    LOG_INFO(kRoleManage, QString("发送订阅主动上报消息：%1").arg(subscribe_topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, subscribe_topics);
}

RoleManage::~RoleManage()
{

}

void RoleManage::SlotActionResponse(const QJsonObject& response_data)
{
    LOG_INFO(kRoleManage, QString("收到外部应答：%1").arg(QJsonDocument(response_data).toJson(QJsonDocument::Compact).data()));
    QString type = response_data.value("type").toString();
    if(map_function_response_.keys().contains(type))
    {
        (this->*map_function_response_[type])(response_data);
    }
}

void RoleManage::SlotActionRequest(const QJsonObject& request_data)
{
    LOG_INFO(kRoleManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(map_function_request_.keys().contains(type))
    {
        (this->*map_function_request_[type])(request_data);
    }
}

void RoleManage::SlotPubTopic(const QJsonObject& topic_data)
{
    QString type = topic_data.value("type").toString();
    LOG_INFO(kRoleManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    if(map_function_topic_.keys().contains(type))
    {
        (this->*map_function_topic_[type])(topic_data);
    }
}

void RoleManage::Do_Request_InitLocalRoleInfo(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    m_player_->InitLocalRoleInfo(data);
}

void RoleManage::Do_Request_UpgradeLevel(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_player_->SlotUpgradeLevel();
}

void RoleManage::Do_Request_CyclicLifeUpdate(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_player_->SlotLifeUpdate();
}

void RoleManage::Do_Request_CyclicCultivation(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_player_->SlotCyclicCultivation();
}

void RoleManage::Do_Request_CyclicEnhanceAtt(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_player_->SlotCyclicEnhanceAtt();
}

void RoleManage::Do_Request_ModifyRoleName(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    m_player_->SetRoleName(data.value("name").toString());
}

void RoleManage::Do_Request_IncreModRoleBaseAtt(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    m_player_->IncreModRoleBaseAtt((RoleBaseAttEnum)data.value("att_enum").toInt(), data.value("sum").toInt());
}

void RoleManage::Do_Topic_StartFishing(const QJsonObject& topic_data)
{
    Q_UNUSED(topic_data);
    m_player_->CheckExpIsUpgrade();
}

void RoleManage::Do_Topic_SaveRoleEquip(const QJsonObject& topic_data)
{
    Q_UNUSED(topic_data);
}

void RoleManage::Do_Topic_SaveRoleItem(const QJsonObject& topic_data)
{
    Q_UNUSED(topic_data);
}
