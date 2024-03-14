//
// Created by hu on 2024/3/11.
//
#include "modules/game_progress/progress_manage.h"
#include "modules/public/public_declare.h"

ProgressManage::ProgressManage() {
    m_module_name = module_name::progress;
    game_pro_obj_ = ProgressService::getInstance();
}

int ProgressManage::Init()
{
    return 0;
}

ProgressManage::~ProgressManage()
{

}

void ProgressManage::SlotActionResponse(const QJsonObject& request_data)
{

}

void ProgressManage::SlotActionRequest(const QJsonObject& request_data)
{

}

void ProgressManage::SlotPubTopic(const QJsonObject& status)
{

}
