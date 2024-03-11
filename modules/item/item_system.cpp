//
// Created by hu on 2024/3/11.
//
#include "item_system.h"
#include "modules/public/public_declare.h"

ItemSystem::ItemSystem() {
    m_module_name = module_name::item;
    item_obj_ = ItemManage::getInstance();
}
