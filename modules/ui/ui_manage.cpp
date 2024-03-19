#include "ui_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

UIManage::UIManage()
{
    m_module_name = module_name::ui;
    m_service_ = MainUI::getInstance();

    connect(m_service_, &MainUI::SignalActionRequest, this, &UIManage::SignalActionRequest);
    connect(m_service_, &MainUI::SignalActionResponse, this, &UIManage::SignalActionResponse);
    connect(m_service_, &MainUI::SignalPubTopic, this, &UIManage::SignalPubTopic);
}

UIManage::~UIManage()
{

}

int UIManage::Init() {
    return 0;
}

void UIManage::SlotActionResponse(const QJsonObject &request_data) {

}

void UIManage::SlotActionRequest(const QJsonObject &request_data) {
    LOG_DEBUG(kUIManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(type.contains(uiCmd::ShowMsgToUI))
    {
        QJsonObject data_obj = request_data.value("data").toObject();
        QString msg = data_obj.value("msg").toString();
        m_service_->SlotShowMsg(msg);
    }
    else if(type.contains(mainCmd::InitRoleInfo))
    {
        QJsonObject data_obj = request_data.value("data").toObject();
        UpdateUi(data_obj);
    }

}

void UIManage::SlotPubTopic(const QJsonObject &status) {

}

void UIManage::UpdateUi(QJsonObject role_data) {
    QJsonObject role_info, role_equip, role_item, role_coefficient;
    role_info = role_data.value("RoleInfo").toObject();
    role_equip = role_data.value("RoleEquip").toObject();
    role_item = role_data.value("RoleItem").toObject();
    QString role_name = role_info.value("role_name").toString();
    QString role_life = role_info.value("role_life").toString();
    QString role_prestige = role_info.value("role_prestige").toString();
    int role_LV = role_info.value("role_lv").toString().toInt();

    QString role_cur_exp = role_info.value("role_cur_exp").toString();
    QString role_agg = role_info.value("role_agg").toString();
    QString role_def = role_info.value("role_def").toString();
    QString role_hp = role_info.value("role_hp").toString();

    QString equip_weapon = role_equip.value("equip_weapon").toString();
    QString equip_magic = role_equip.value("equip_magic").toString();
    QString equip_helmet = role_equip.value("equip_helmet").toString();
    QString equip_clothing = role_equip.value("equip_clothing").toString();
    QString equip_britches = role_equip.value("equip_britches").toString();
    QString equip_shoe = role_equip.value("equip_shoe").toString();
    QString equip_jewelry = role_equip.value("equip_jewelry").toString();
    QString equip_mount = role_equip.value("equip_mount").toString();
    QString equip_title = role_equip.value("equip_title").toString();
    m_service_->UpdateRoleInformation(role_name, role_life, role_prestige, PublicFunc::GetCultivationName(role_LV));
    m_service_->UpdatePhysicalStrength(role_cur_exp, role_agg, role_def, role_hp);
    m_service_->UpdateEquip(equip_weapon, equip_magic, equip_helmet, equip_clothing, equip_britches,
                            equip_shoe, equip_jewelry, equip_mount, equip_title);
}
