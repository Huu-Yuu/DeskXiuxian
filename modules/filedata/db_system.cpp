//
// Created by hu on 2024/3/11.
//
#include "db_system.h"
#include "modules/public/public_declare.h"

DBSystem::DBSystem() {
    m_module_name = module_name::data;
    data_obj_ = DataManage::getInstance();
}

int DBSystem::Init()
{
    return 0;
}

DBSystem::~DBSystem()
{

}

void DBSystem::SlotActionResponse(const QJsonObject& request_data)
{

}

void DBSystem::SlotActionRequest(const QJsonObject& request_data)
{

}

void DBSystem::SlotPubTopic(const QJsonObject& status)
{

}
