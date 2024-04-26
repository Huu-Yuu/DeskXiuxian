#include "item_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

ItemManage::ItemManage() {
    m_module_name = module_name::item;
    m_service_ = ItemService::getInstance();
    connect(m_service_, &ItemService::SignalActionRequest, this, &ItemManage::SignalActionRequest);
    connect(m_service_, &ItemService::SignalActionResponse, this, &ItemManage::SignalActionResponse);
    connect(m_service_, &ItemService::SignalPubTopic, this, &ItemManage::SignalPubTopic);

    map_function_request_[mainCmd::InitLocalRoleInfo] = &ItemManage::Do_Request_InitLocalRoleInfo;
    map_function_request_[itemCmd::IncreaseMoney] = &ItemManage::Do_Request_IncreaseMoney;
    map_function_request_[uiCmd::UpdatePropShow] = &ItemManage::Do_Request_UpdatePropShow;
    map_function_request_[itemCmd::UseProps] = &ItemManage::Do_Request_UseProps;

    map_function_topic_[itemCmd::UsePropsSuccessful] = &ItemManage::Do_Topic_UsePropsSuccessful;
}

int ItemManage::Init()
{
    QStringList db_topics = QStringList{dbCmd::SaveRoleEquip, dbCmd::SaveRoleItem};
    QStringList item_topics = QStringList{itemCmd::UsePropsSuccessful};
    QStringList topics;
    topics += db_topics;
    topics += item_topics;
    LOG_DEBUG(kItemManage, QString("发送订阅主动上报消息：%1").arg(topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, topics);
}

ItemManage::~ItemManage()
{

}

void ItemManage::SlotActionResponse(const QJsonObject& response_data)
{
    LOG_DEBUG(kRoleManage, QString("收到外部应答：%1").arg(QJsonDocument(response_data).toJson(QJsonDocument::Compact).data()));
    QString type = response_data.value("type").toString();
    if(map_function_rsponse_.keys().contains(type))
    {
        (this->*map_function_rsponse_[type])(response_data);
    }
}

void ItemManage::SlotActionRequest(const QJsonObject& request_data)
{
    LOG_DEBUG(kRoleManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(map_function_request_.keys().contains(type))
    {
        (this->*map_function_request_[type])(request_data);
    }
}

void ItemManage::SlotPubTopic(const QJsonObject& topic_data)
{
    LOG_DEBUG(kItemManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    QString type = topic_data.value("type").toString();
    if(map_function_topic_.keys().contains(type))
    {
        (this->*map_function_topic_[type])(topic_data);
    }
}

void ItemManage::Do_Request_InitLocalRoleInfo(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    m_service_->InitLocalRoleInfo(data);
}

void ItemManage::Do_Request_IncreaseMoney(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    int money_nun = data.value("num").toInt();
    m_service_->ItemMoneyBusiness(money_nun);
}

void ItemManage::Do_Request_UpdatePropShow(const QJsonObject& request_data)
{
     m_service_->UpdatePropShow(request_data);
}

void ItemManage::Do_Request_UseProps(const QJsonObject& request_data)
{
    QJsonObject data = request_data.value("data").toObject();
    int index = data.value("prop_index").toInt();
    int num = data.value("num").toInt();
    m_service_->DeductPropNum(index, num);
}

void ItemManage::Do_Topic_UsePropsSuccessful(const QJsonObject& topic_data)
{
    QJsonObject data = topic_data.value("data").toObject();
    int result = data.value("result").toInt();
    int index = data.value("prop_index").toInt();
    int num = data.value("num").toInt();
    if(result == 1)
    {
        m_service_->UseProps(index, num);
    }
    else
    {
        m_service_->IncrementItem(index, num);  // 数据库扣除数量失败，则需要将数量给改回去
    }
}
