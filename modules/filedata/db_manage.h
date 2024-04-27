#ifndef DESKXIUXINA_DB_MANAGE_H
#define DESKXIUXINA_DB_MANAGE_H
#include <QObject>
#include "modules/interface_manager.h"
#include "data_service.h"

class DBManage : public InterfaceManager
{
    Q_OBJECT
public:
    DBManage();
    ~DBManage();
    int Init() override;
    typedef void (DBManage::*Function_)(const QJsonObject&);
public slots:
    void SlotActionResponse(const QJsonObject& response_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& topic_data) override;

private:
    void Do_Request_InitLocalRoleInfo(const QJsonObject& request_data);
    void Do_Request_InitRemoteRoleInfo(const QJsonObject& request_data);
    void Do_Request_AutomaticLogin(const QJsonObject& request_data);
    void Do_Request_CheckLoginFist(const QJsonObject& request_data);
    void Do_Request_ModifyRoleName(const QJsonObject& request_data);
    void Do_Request_CheckRoleNameIsOk(const QJsonObject& request_data);
    void Do_Request_LoginVerification(const QJsonObject& request_data);
    void Do_Request_SetUserInfoToConfig(const QJsonObject& request_data);
    void Do_Request_AccountRegistration(const QJsonObject& request_data);
    void Do_Request_UpdateLastLoginTime(const QJsonObject& request_data);

    void Do_Topic_SaveRoleEquip(const QJsonObject& topic_data);
    void Do_Topic_SaveRoleInfo(const QJsonObject& topic_data);
    void Do_Topic_SaveCoefficient(const QJsonObject& topic_data);
    void Do_Topic_SaveRoleItem(const QJsonObject& topic_data);

private:
    DataService* m_service_;
    QMap<QString, Function_> map_function_request_;
    QMap<QString, Function_> map_function_topic_;
    QMap<QString, Function_> map_function_response_;
};

#endif //DESKXIUXINA_DB_MANAGE_H
