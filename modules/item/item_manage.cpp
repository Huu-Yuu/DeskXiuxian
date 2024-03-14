//
// Created by hu on 2024/3/11.
//
#include "item_manage.h"
#include "modules/public/public_declare.h"

ItemManage::ItemManage() {
    m_module_name = module_name::item;
    item_obj_ = ItemService::getInstance();
    connect(item_obj_, &ItemService::SignalActionRequest, this, &ItemManage::SignalActionRequest);
    connect(item_obj_, &ItemService::SignalActionResponse, this, &ItemManage::SignalActionResponse);
    connect(item_obj_, &ItemService::SignalPubTopic, this, &ItemManage::SignalPubTopic);
}

int ItemManage::Init()
{
    return 0;
}

ItemManage::~ItemManage()
{

}

void ItemManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void ItemManage::SlotActionRequest(const QJsonObject& request_data)
{

}

void ItemManage::SlotPubTopic(const QJsonObject& status)
{

}
