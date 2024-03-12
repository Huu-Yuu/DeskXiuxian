//
// Created by hu on 2024/3/11.
//
#include "role_system.h"
#include "modules/public/public_declare.h"

RoleSystem::RoleSystem() {
    m_module_name = module_name::role;
    role_obj_ = RolePlayer::getInstance();
}

int RoleSystem::Init()
{
    return 0;
}

RoleSystem::~RoleSystem()
{

}

void RoleSystem::SlotActionResponse(const QJsonObject& request_data)
{

}

void RoleSystem::SlotActionRequest(const QJsonObject& request_data)
{

}

void RoleSystem::SlotPubTopic(const QJsonObject& status)
{
}
