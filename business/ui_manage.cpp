#include "business/ue_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

UIManage::UIManage()
{
    m_module_name = module_name::ui;
    m_service_ = MainUI::getInstance();

    connect(m_service_, &MainUI::SignalActionRequest, this, &UIManage::SignalActionRequest);
    connect(m_service_, &MainUI::SignalActionResponse, this, &UIManage::SignalActionResponse);
    connect(m_service_, &MainUI::SignalPubTopic, this, &UIManage::SignalPubTopic);

    map_function_request_[mainCmd::InitLocalRoleInfo] = &UIManage::Do_Request_InitLocalRoleInfo;
    map_function_request_[uiCmd::ShowMsgToUI] = &UIManage::Do_Request_ShowMsgToUI;
    map_function_request_[uiCmd::DisableCultivaUpButton] = &UIManage::Do_Request_DisableCultivaUpButton;
    map_function_request_[uiCmd::UpdateRoleUI] = &UIManage::Do_Request_UpdateRoleUI;
    map_function_request_[uiCmd::ActivateCultivaUpButton] = &UIManage::Do_Request_ActivateCultivaUpButton;
    map_function_request_[uiCmd::InitRoleUI] = &UIManage::Do_Request_InitRoleUI;
    map_function_request_[uiCmd::ShowMainUI] = &UIManage::Do_Request_ShowMainUI;
    map_function_request_[uiCmd::ShowLoginWidget] = &UIManage::Do_Request_ShowLoginWidget;
    map_function_request_[uiCmd::ShowRenameWidget] = &UIManage::Do_Request_ShowRenameWidget;

    map_function_response_[dbCmd::CheckLoginFist] = &UIManage::Do_Response_CheckLoginFist;
    map_function_response_[dbCmd::CheckRoleNameIsOk] = &UIManage::Do_Response_CheckRoleNameIsOk;
    map_function_response_[dbCmd::LoginVerification] = &UIManage::Do_Response_LoginVerification;
    map_function_response_[dbCmd::AccountRegistration] = &UIManage::Do_Response_AccountRegistration;
    map_function_response_[dbCmd::UpdateLastLoginTime] = &UIManage::Do_Response_UpdateLastLoginTime;
    map_function_response_[mainCmd::AutomaticLogin] = &UIManage::Do_Response_AutomaticLogin;
    map_function_response_[roleCmd::ModifyRoleName] = &UIManage::Do_Response_ModifyRoleName;
    map_function_response_[uiCmd::UpdatePropShow] = &UIManage::Do_Response_UpdatePropShow;

    map_function_topic_[itemCmd::UsePropsSuccessful] = &UIManage::Do_Topic_UsePropsSuccessful;
}

UIManage::~UIManage()
{

}

int UIManage::Init() {
    QStringList item_topics = QStringList{itemCmd::UsePropsSuccessful};
    QStringList topics;
    topics += item_topics;
    LOG_INFO(kItemManage, QString("发送订阅主动上报消息：%1").arg(topics.join(",").toStdString().c_str()));
    emit SignalSubTopic(kSubType, topics);
    return 0;
}

void UIManage::SlotActionResponse(const QJsonObject &response_data) {
    LOG_INFO(kUIManage, QString("收到外部应答：%1").arg(QJsonDocument(response_data).toJson(QJsonDocument::Compact).data()));
    QString type = response_data.value("type").toString();

    if(map_function_response_.keys().contains(type))
    {
        (this->*map_function_response_[type])(response_data);
    }
}

void UIManage::SlotActionRequest(const QJsonObject &request_data) {
    LOG_INFO(kUIManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(map_function_request_.keys().contains(type))
    {
        (this->*map_function_request_[type])(request_data);
    }
}

void UIManage::SlotPubTopic(const QJsonObject &topic_data) {
    LOG_INFO(kUIManage, QString("收到广播信息：%1").arg(QJsonDocument(topic_data).toJson(QJsonDocument::Compact).data()));
    QString type = topic_data.value("type").toString();
    if(map_function_topic_.keys().contains(type))
    {
        (this->*map_function_topic_[type])(topic_data);
    }

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

void UIManage::Do_Request_ShowMsgToUI(const QJsonObject& request_data)
{
    QJsonObject data_obj = request_data.value("data").toObject();
    QString msg = data_obj.value("msg").toString();
    m_service_->SlotShowMsg(msg);
}

void UIManage::Do_Request_InitLocalRoleInfo(const QJsonObject& request_data)
{
    QJsonObject data_obj = request_data.value("data").toObject();
    UpdateUi(data_obj);
}

void UIManage::Do_Request_DisableCultivaUpButton(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_service_->SlotDisableCultivaUpButton();
}

void UIManage::Do_Request_UpdateRoleUI(const QJsonObject& request_data)
{
    QJsonObject data_obj = request_data.value("data").toObject();
    m_service_->UpdateRoleUI(data_obj);
}

void UIManage::Do_Request_ActivateCultivaUpButton(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_service_->SlotActivateCultivaUpButton();
}

void UIManage::Do_Request_InitRoleUI(const QJsonObject& request_data)
{
    QJsonObject data_obj = request_data.value("data").toObject();
    QJsonObject role_info_data, role_item_data, role_rc_data, role_equic_data;
    role_info_data = data_obj.value("role_info_data").toObject();
    role_item_data = data_obj.value("role_item_data").toObject();
    role_rc_data = data_obj.value("role_rc_data").toObject();
    role_equic_data = data_obj.value("role_equic_data").toObject();
    m_service_->InitRoleUI(role_info_data, role_item_data, role_rc_data, role_equic_data);
}

void UIManage::Do_Request_ShowMainUI(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_service_->show();
}

void UIManage::Do_Request_ShowLoginWidget(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_service_->ShowLoginWidget();
}

void UIManage::Do_Request_ShowRenameWidget(const QJsonObject& request_data)
{
    Q_UNUSED(request_data);
    m_service_->ShowModifyNameWidget();
}

void UIManage::Do_Response_CheckLoginFist(const QJsonObject& response_data)
{
    QJsonObject data_obj = response_data.value("data").toObject();
    int result = data_obj.value("result").toInt();
    m_service_->FistLogInDeal(result);
}

void UIManage::Do_Response_AutomaticLogin(const QJsonObject& response_data)
{
    QJsonObject data_obj = response_data.value("data").toObject();
    int result = data_obj.value("result").toInt();
    m_service_->AutomaticLogin(result);
}

void UIManage::Do_Response_ModifyRoleName(const QJsonObject& response_data)
{
    QJsonObject data_obj = response_data.value("data").toObject();
    int result = data_obj.value("result").toInt();
    m_service_->ModifyRoleNameDeal(result);
}

void UIManage::Do_Response_CheckRoleNameIsOk(const QJsonObject& response_data)
{
    QJsonObject data_obj = response_data.value("data").toObject();
    int result = data_obj.value("result").toInt();
    m_service_->RoleNameIsOkDeal(result);
}

void UIManage::Do_Response_LoginVerification(const QJsonObject& response_data)
{
    QJsonObject data_obj = response_data.value("data").toObject();
    int result = data_obj.value("result").toInt();
    m_service_->LoginVerificationDeal(result);
}

void UIManage::Do_Response_AccountRegistration(const QJsonObject& response_data)
{
    QJsonObject data_obj = response_data.value("data").toObject();
    int result = data_obj.value("result").toInt();
    m_service_->AccountRegistrationDeal(result);
}

void UIManage::Do_Response_UpdateLastLoginTime(const QJsonObject& response_data)
{
    Q_UNUSED(response_data);
    LOG_INFO(kUIManage, "关闭窗口");
}

void UIManage::Do_Response_UpdatePropShow(const QJsonObject& response_data)
{
    QJsonObject data_obj = response_data.value("data").toObject();
    m_service_->UpdateBackpackBar(data_obj);
}

void UIManage::Do_Topic_UsePropsSuccessful(const QJsonObject& topic_data)
{
    QJsonObject data = topic_data.value("data").toObject();
    int result = data.value("result").toInt();
    int index = data.value("prop_index").toInt();
    int num = data.value("num").toInt();
    if(result == 1)
    {
        m_service_->RequestOutside(uiCmd::UpdatePropShow, module_name::item);
    }
    else
    {
        m_service_->AddMessage("道具使用失败");
    }
}
