#include "db_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

DBManage::DBManage() {
    m_module_name = module_name::data;
    m_service_ = DataService::getInstance();

    connect(m_service_, &DataService::SignalActionRequest, this, &DBManage::SignalActionRequest);
    connect(m_service_, &DataService::SignalActionResponse, this, &DBManage::SignalActionResponse);
    connect(m_service_, &DataService::SignalPubTopic, this, &DBManage::SignalPubTopic);
}

int DBManage::Init()
{
    QStringList db_topics = QStringList{dbCmd::SaveRoleEquip, dbCmd::SaveRoleItem, dbCmd::SaveRoleInfo, dbCmd::SaveCoefficient};
    QStringList subscribe_topics;
    subscribe_topics += db_topics;
    LOG_DEBUG(kDataManage, QString("发送订阅主动上报消息：%1").arg(subscribe_topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, subscribe_topics);
}

DBManage::~DBManage()
{

}

void DBManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void DBManage::SlotActionRequest(const QJsonObject& request_data)
{
    LOG_DEBUG(kRoleManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(type.contains(mainCmd::InitLocalRoleInfo))
    {
        m_service_->InitLocalRoleInfo();
    }
    else if(type.contains(mainCmd::InitRemoteRoleInfo))
    {
        m_service_->InitRemoteRoleInfo();
    }
    else if(type.contains(dbCmd::CheckLogInFist))
    {
        int result = m_service_->CheckUserLogginIsFist();   ///< 0-非首次登录  1-首次登录
        QJsonObject data_obj;
        data_obj.insert("result", result);
        emit SignalActionResponse(PublicFunc::PackageResponse(dbCmd::CheckLogInFist,
                                                              request_data.value("id").toString(),
                                                              0,
                                                              data_obj,
                                                              QJsonObject(),
                                                              request_data.value("ori").toString(),
                                                              module_name::data));
    }
    else if(type.contains(mainCmd::AutomaticLogin))
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
}

void DBManage::SlotPubTopic(const QJsonObject& topic_data)
{
    LOG_DEBUG(kDataManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    QString type = topic_data.value("type").toString();
    if(type.contains(dbCmd::SaveRoleEquip))
    {
        QJsonObject data = topic_data.value("data").toObject();
        m_service_->SlotSaveRoleEquipToDatabase(data);
    }
    else if(type.contains(dbCmd::SaveRoleInfo))
    {
        QJsonObject data = topic_data.value("data").toObject();
        m_service_->SlotSaveRoleInfoToDatabase(data);
    }
    else if(type.contains(dbCmd::SaveCoefficient))
    {
        QJsonObject data = topic_data.value("data").toObject();
        m_service_->SlotSaveRoleCoefficientToDatabase(data);
    }
    else if(type.contains(dbCmd::SaveRoleItem))
    {
        QJsonObject data = topic_data.value("data").toObject();
        m_service_->SlotSaveRoleItemToDatabase(data);
    }
}
