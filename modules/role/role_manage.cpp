#include "role_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

RoleManage::RoleManage() {
    m_module_name = module_name::role;
    m_player_ = RolePlayer::getInstance();

    connect(m_player_, &RolePlayer::SignalActionRequest, this, &RoleManage::SignalActionRequest);
    connect(m_player_, &RolePlayer::SignalActionResponse, this, &RoleManage::SignalActionResponse);
    connect(m_player_, &RolePlayer::SignalPubTopic, this, &RoleManage::SignalPubTopic);
}

int RoleManage::Init()
{
    QStringList db_topics = QStringList{dbCmd::SaveRoleEquip, dbCmd::SaveRoleItem};
    QStringList ui_topics = QStringList{uiCmd::StartFishing};
    QStringList subscribe_topics;
    subscribe_topics += db_topics;
    subscribe_topics += ui_topics;
    LOG_DEBUG(kRoleManage, QString("发送订阅主动上报消息：%1").arg(subscribe_topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, subscribe_topics);
}

RoleManage::~RoleManage()
{

}

void RoleManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void RoleManage::SlotActionRequest(const QJsonObject& request_data)
{
    LOG_DEBUG(kRoleManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(type.contains(mainCmd::InitLocalRoleInfo))
    {
        QJsonObject data = request_data.value("data").toObject();
        m_player_->InitLocalRoleInfo(data);
    }
    else if(type.contains(uiCmd::UpgradeLevel))
    {
        m_player_->SlotUpgradeLevel();
    }
    else if(type.contains(ProgressCmd::CyclicLifeUpdate))
    {
        m_player_->SlotLifeUpdate();
    }
    else if(type.contains(ProgressCmd::CyclicCultivation))
    {
        m_player_->SlotCyclicCultivation();
    }
    else if(type.contains(ProgressCmd::CyclicEnhanceAtt))
    {
        m_player_->SlotCyclicEnhanceAtt();
    }
}

void RoleManage::SlotPubTopic(const QJsonObject& topic_data)
{
    QString type = topic_data.value("type").toString();
    LOG_DEBUG(kRoleManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    if(type.contains(dbCmd::SaveRoleEquip))
    {

    }
    else if(type.contains(dbCmd::SaveRoleItem))
    {

    }
    else if(type.contains(uiCmd::StartFishing))
    {
        m_player_->CheckExpIsUpgrade();
    }
}

