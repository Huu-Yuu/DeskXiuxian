//
// Created by hu on 2024/3/11.
//
#include "role_manage.h"
#include "modules/public/public_declare.h"

RoleManage::RoleManage() {
    m_module_name = module_name::role;
    role_obj_ = RolePlayer::getInstance();
}

int RoleManage::Init()
{
    return 0;
}

RoleManage::~RoleManage()
{

}

void RoleManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void RoleManage::SlotActionRequest(const QJsonObject& request_data)
{

}

void RoleManage::SlotPubTopic(const QJsonObject& status)
{
}

