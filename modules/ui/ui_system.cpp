#include "ui_system.h"
#include "modules/public/public_declare.h"

UISystem::UISystem()
{
    m_module_name = module_name::userinterface;
    ui_obj_ = MainUI::getInstance();
}