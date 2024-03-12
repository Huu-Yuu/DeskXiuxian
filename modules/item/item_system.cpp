//
// Created by hu on 2024/3/11.
//
#include "item_system.h"
#include "modules/public/public_declare.h"

ItemSystem::ItemSystem() {
    m_module_name = module_name::item;
    item_obj_ = ItemManage::getInstance();
}

int ItemSystem::Init()
{
    return 0;
}

ItemSystem::~ItemSystem()
{

}

void ItemSystem::SlotActionResponse(const QJsonObject& request_data)
{

}

void ItemSystem::SlotActionRequest(const QJsonObject& request_data)
{

}

void ItemSystem::SlotPubTopic(const QJsonObject& status)
{

}
