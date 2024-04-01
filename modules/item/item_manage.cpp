#include "item_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

ItemManage::ItemManage() {
    m_module_name = module_name::item;
    m_service_ = ItemService::getInstance();
    connect(m_service_, &ItemService::SignalActionRequest, this, &ItemManage::SignalActionRequest);
    connect(m_service_, &ItemService::SignalActionResponse, this, &ItemManage::SignalActionResponse);
    connect(m_service_, &ItemService::SignalPubTopic, this, &ItemManage::SignalPubTopic);
}

int ItemManage::Init()
{
    QStringList db_topics = QStringList{dbCmd::SaveRoleEquip, dbCmd::SaveRoleItem};

    LOG_DEBUG(kItemManage, QString("发送订阅主动上报消息：%1").arg(db_topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, db_topics);
}

ItemManage::~ItemManage()
{

}

void ItemManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void ItemManage::SlotActionRequest(const QJsonObject& request_data)
{
    LOG_DEBUG(kRoleManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(type.contains(mainCmd::InitLocalRoleInfo))
    {
        QJsonObject data = request_data.value("data").toObject();
        m_service_->InitLocalRoleInfo(data);
    }
    else if(type.contains(itemCmd::IncreaseMoney))
    {
        QJsonObject data = request_data.value("data").toObject();
        int money_nun = data.value("num").toInt();
        m_service_->ItemMoneyBusiness(money_nun);
    }
    else if(type.contains(uiCmd::UpdatePropShow))
    {
        m_service_->UpdatePropShow(request_data);
    }
    else if(type.contains(itemCmd::UseProps))
    {
        QJsonObject data = request_data.value("data").toObject();
        int index = data.value("props_index").toInt();
        int num = data.value("num").toInt();
        m_service_->UseProps(index, num);
    }
}

void ItemManage::SlotPubTopic(const QJsonObject& topic_data)
{
    LOG_DEBUG(kItemManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    QString type = topic_data.value("type").toString();
}
