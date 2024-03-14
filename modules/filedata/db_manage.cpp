//
// Created by hu on 2024/3/11.
//
#include "db_manage.h"
#include "modules/public/public_declare.h"

DBManage::DBManage() {
    m_module_name = module_name::data;
    data_obj_ = DataService::getInstance();
}

int DBManage::Init()
{
    return 0;
}

DBManage::~DBManage()
{

}

void DBManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void DBManage::SlotActionRequest(const QJsonObject& request_data)
{

}

void DBManage::SlotPubTopic(const QJsonObject& status)
{

}
