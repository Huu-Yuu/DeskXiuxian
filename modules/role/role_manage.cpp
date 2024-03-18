#include "role_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

RoleManage::RoleManage() {
    m_module_name = module_name::role;
    role_obj_ = RolePlayer::getInstance();
}

int RoleManage::Init()
{
    QStringList db_topics = QStringList{dbCmd::SaveRoleEquip, dbCmd::SaveRoleItem};

    LOG_DEBUG(kRoleManage, QString("发送订阅主动上报消息：%1").arg(db_topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, db_topics);
}

RoleManage::~RoleManage()
{

}

void RoleManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void RoleManage::SlotActionRequest(const QJsonObject& request_data)
{
    LOG_DEBUG(kUIManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(type.contains(mainCmd::InitRoleInfo))
    {
        QJsonObject data = request_data.value("data").toObject();
        role_obj_->InitLocalRoleInfo(data);
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
}

