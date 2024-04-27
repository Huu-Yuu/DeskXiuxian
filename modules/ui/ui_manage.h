#ifndef DESKXIUXINA_UI_MANAGE_H
#define DESKXIUXINA_UI_MANAGE_H
#include <QObject>
#include "modules/interface_manager.h"
#include "mainui.h"

class UIManage : public InterfaceManager
{
Q_OBJECT
public:
    UIManage();
    ~UIManage();
    int Init() override;
    typedef void (UIManage::*Function_)(const QJsonObject&) ;
public slots:
    void SlotActionResponse(const QJsonObject& response_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& topic_data) override;
private:
    void Do_Request_ShowMsgToUI(const QJsonObject& request_data);
    void Do_Request_InitLocalRoleInfo(const QJsonObject& request_data);
    void Do_Request_DisableCultivaUpButton(const QJsonObject& request_data);
    void Do_Request_UpdateRoleUI(const QJsonObject& request_data);
    void Do_Request_ActivateCultivaUpButton(const QJsonObject& request_data);
    void Do_Request_InitRoleUI(const QJsonObject& request_data);
    void Do_Request_ShowMainUI(const QJsonObject& request_data);
    void Do_Request_ShowLoginWidget(const QJsonObject& request_data);
    void Do_Request_ShowRenameWidget(const QJsonObject& request_data);

    void Do_Response_CheckLoginFist(const QJsonObject& response_data);
    void Do_Response_AutomaticLogin(const QJsonObject& response_data);
    void Do_Response_ModifyRoleName(const QJsonObject& response_data);
    void Do_Response_CheckRoleNameIsOk(const QJsonObject& response_data);
    void Do_Response_LoginVerification(const QJsonObject& response_data);
    void Do_Response_AccountRegistration(const QJsonObject& response_data);
    void Do_Response_UpdateLastLoginTime(const QJsonObject& response_data);
    void Do_Response_UpdatePropShow(const QJsonObject& response_data);

    void Do_Topic_UsePropsSuccessful(const QJsonObject& topic_data);

private:
    void UpdateUi(const QJsonObject& role_data);
    MainUI* m_service_;
    QMap<QString, Function_> map_function_request_;
    QMap<QString, Function_> map_function_response_;
    QMap<QString, Function_> map_function_topic_;
};
#endif //DESKXIUXINA_UI_MANAGE_H
