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

QString InterfaceManager::getModuleName()
{
    return m_module_name;
}

void InterfaceManager::slotActionResponse(const QJsonObject& response_data)
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

void InterfaceManager::slotActionRequest(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
}

void InterfaceManager::slotPubTopic(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
}

