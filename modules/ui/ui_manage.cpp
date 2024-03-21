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

void UIManage::SlotActionResponse(const QJsonObject &response_data) {
    LOG_DEBUG(kUIManage, QString("收到外部应答：%1").arg(QJsonDocument(response_data).toJson(QJsonDocument::Compact).data()));
    QString type = response_data.value("type").toString();
    QJsonObject data_obj = response_data.value("data").toObject();
    if(type.contains(dbCmd::CheckLogInFist))
    {
        int result = data_obj.value("result").toInt();
        m_service_->FistLogInDeal(result);
    }
    else if(type.contains(mainCmd::AutomaticLogin))
    {
        int result = data_obj.value("result").toInt();
        m_service_->AutomaticLogin(result);
    }
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
    else if(type.contains(mainCmd::InitLocalRoleInfo))
    {
        QJsonObject data_obj = request_data.value("data").toObject();
        UpdateUi(data_obj);
    }
    else if(type.contains(uiCmd::DisableCultivaUpButton))
    {
        m_service_->SlotDisableCultivaUpButton();
    }
    else if(type.contains(uiCmd::UpdateRoleUI))
    {
        QJsonObject data_obj = request_data.value("data").toObject();
        m_service_->UpdateRoleUI(data_obj);
    }
    else if(type.contains(uiCmd::ActivateCultivaUpButton))
    {
        m_service_->SlotActivateCultivaUpButton();
    }
    else if(type.contains(uiCmd::InitRoleUI))
    {
        QJsonObject data_obj = request_data.value("data").toObject();
        QJsonObject role_info_data, role_item_data, role_rc_data, role_equic_data;
        role_info_data = data_obj.value("role_info_data").toObject();
        role_item_data = data_obj.value("role_item_data").toObject();
        role_rc_data = data_obj.value("role_rc_data").toObject();
        role_equic_data = data_obj.value("role_equic_data").toObject();
        m_service_->InitRoleUI(role_info_data, role_item_data, role_rc_data, role_equic_data);
    }
    else if(type.contains(uiCmd::ShowMainUI))
    {
        m_service_->show();
    }
    else if(type.contains(uiCmd::ShowLoginWidget))
    {
        m_service_->ShowLoginWidget();
    }
}

void UIManage::SlotPubTopic(const QJsonObject &topic_data) {

}

void UIManage::UpdateUi(const QJsonObject& role_data) {
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
