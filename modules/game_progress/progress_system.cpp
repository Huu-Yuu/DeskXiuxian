//
// Created by hu on 2024/3/11.
//
#include "modules/game_progress/progress_system.h"
#include "modules/public/public_declare.h"

ProgressSystem::ProgressSystem() {
    m_module_name = module_name::progress;
    game_pro_obj_ = GameProgress::getInstance();
}

int ProgressSystem::Init()
{
    return 0;
}

ProgressSystem::~ProgressSystem()
{

}

void ProgressSystem::SlotActionResponse(const QJsonObject& request_data)
{

}

void ProgressSystem::SlotActionRequest(const QJsonObject& request_data)
{

}

void ProgressSystem::SlotPubTopic(const QJsonObject& status)
{

}
