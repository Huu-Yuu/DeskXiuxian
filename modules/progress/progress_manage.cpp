#include "modules/progress/progress_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

ProgressManage::ProgressManage() {
    m_module_name = module_name::progress;
    game_pro_obj_ = ProgressService::getInstance();
}

int ProgressManage::Init()
{
    return 0;
}

ProgressManage::~ProgressManage()
{

}

void ProgressManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void ProgressManage::SlotActionRequest(const QJsonObject& request_data)
{

}

void ProgressManage::SlotPubTopic(const QJsonObject& topic_data)
{
    LOG_DEBUG(kProgressManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    QString type = topic_data.value("type").toString();
}
