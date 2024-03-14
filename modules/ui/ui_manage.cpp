#include "ui_manage.h"
#include "modules/public/public_declare.h"

UIManage::UIManage()
{
    m_module_name = module_name::userinterface;
    ui_obj_ = MainUI::getInstance();
}

int UIManage::Init() {
    return 0;
}

void UIManage::SlotActionResponse(const QJsonObject &request_data) {

}

void UIManage::SlotActionRequest(const QJsonObject &request_data) {

}

void UIManage::SlotPubTopic(const QJsonObject &status) {

}
