//
// Created by hu on 2024/3/11.
//
#include "ui_system.h"
#include "modules/public/public_declare.h"

UISystem::UISystem()
{
    m_module_name = module_name::ui;
    ui_obj_ = MainUI::getInstance();
}