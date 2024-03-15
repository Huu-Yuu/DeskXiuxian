//
// Created by hu on 2024/3/11.
//

#include "interface_manager.h"

InterfaceManager::InterfaceManager()
{

}

InterfaceManager::~InterfaceManager()
{

}

QString InterfaceManager::GetModuleName()
{
    return m_module_name;
}

void InterfaceManager::SlotActionResponse(const QJsonObject& response_data)
{
    Q_UNUSED(response_data);
}

//QString InterfaceManager::getParam(const QString& type, const QString& int_out_param)
//{
//    Q_UNUSED(type)
//    Q_UNUSED(int_out_param);
//    return "";
//}

//int InterfaceManager::setParam(const QString& type, const QString& int_out_param)
//{
//    Q_UNUSED(type)
//    Q_UNUSED(int_out_param)
//    return 0;
//}

void InterfaceManager::SlotActionRequest(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
}

void InterfaceManager::SlotPubTopic(const QJsonObject& topic_data)
{
    Q_UNUSED(topic_data);
}

