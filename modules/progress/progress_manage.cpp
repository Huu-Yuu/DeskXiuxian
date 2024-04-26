#include "modules/progress/progress_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

ProgressManage::ProgressManage() {
    m_module_name = module_name::progress;
    m_service_ = ProgressService::getInstance();

    connect(m_service_, &ProgressService::SignalActionRequest, this, &ProgressManage::SignalActionRequest);
    connect(m_service_, &ProgressService::SignalActionResponse, this, &ProgressManage::SignalActionResponse);
    connect(m_service_, &ProgressService::SignalPubTopic, this, &ProgressManage::SignalPubTopic);

    map_function_topic_[uiCmd::StartFishing] = &ProgressManage::Do_Topic_StartFishing;
    map_function_topic_[uiCmd::StopFishing] = &ProgressManage::Do_Topic_StopFishing;
}

int ProgressManage::Init()
{
    QStringList ui_topics = QStringList{uiCmd::StartFishing, uiCmd::StopFishing};

    QStringList subscribe_topics;
    subscribe_topics += ui_topics;
    LOG_DEBUG(kItemManage, QString("发送订阅主动上报消息：%1").arg(subscribe_topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, subscribe_topics);
}

ProgressManage::~ProgressManage()
{

}

void ProgressManage::SlotActionResponse(const QJsonObject& response_data)
{
    LOG_DEBUG(kProgressManage, QString("收到外部请求：%1").arg(QJsonDocument(response_data).toJson(QJsonDocument::Compact).data()));
    QString type = response_data.value("type").toString();
    if(map_function_response_.keys().contains(type))
    {
        (this->*map_function_response_[type])(response_data);
    }
}

void ProgressManage::SlotActionRequest(const QJsonObject& request_data)
{
    LOG_DEBUG(kProgressManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(map_function_request_.keys().contains(type))
    {
        (this->*map_function_request_[type])(request_data);
    }
}

void ProgressManage::SlotPubTopic(const QJsonObject& topic_data)
{
    LOG_DEBUG(kProgressManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    QString type = topic_data.value("type").toString();
    if(map_function_topic_.keys().contains(type))
    {
        (this->*map_function_topic_[type])(topic_data);
    }
}

void ProgressManage::Do_Topic_StartFishing(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_service_->StarPractic();
}

void ProgressManage::Do_Topic_StopFishing(const QJsonObject& request_data)
{
     m_service_->StopPractic();
}
