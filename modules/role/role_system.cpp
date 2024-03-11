//
// Created by hu on 2024/3/11.
//
#include "role_system.h"
#include "modules/public/public_declare.h"

RoleSystem::RoleSystem() {
    m_module_name = module_name::role;
    role_obj_ = RolePlayer::getInstance();
}
