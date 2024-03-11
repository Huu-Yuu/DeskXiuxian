//
// Created by hu on 2024/3/11.
//
#include "db_system.h"
#include "modules/public/public_declare.h"

DBSystem::DBSystem() {
    m_module_name = module_name::configuration;
    data_obj_ = DataManage::getInstance();
}

