//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_ROLE_MANAGE_H
#define DESKXIUXINA_ROLE_MANAGE_H
#include <QObject>
#include "modules/interface_manager.h"
#include "role_player.h"

class RoleManage : public InterfaceManager
{
    Q_OBJECT
public:
    RoleManage();
    ~RoleManage();
    int Init() override;
    typedef void (RoleManage::*Function_Rsp)(const QJsonObject&);
public slots:
    void SlotActionResponse(const QJsonObject& response_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& topic_data) override;
private:
    void Do_Request_InitLocalRoleInfo(const QJsonObject& request_data);
    void Do_Request_UpgradeLevel(const QJsonObject& request_data);
    void Do_Request_CyclicLifeUpdate(const QJsonObject& request_data);
    void Do_Request_CyclicCultivation(const QJsonObject& request_data);
    void Do_Request_CyclicEnhanceAtt(const QJsonObject& request_data);
    void Do_Request_ModifyRoleName(const QJsonObject& request_data);
    void Do_Request_IncreModRoleBaseAtt(const QJsonObject& request_data);

    void Do_Topic_SaveRoleEquip(const QJsonObject& topic_data);
    void Do_Topic_SaveRoleItem(const QJsonObject& topic_data);
    void Do_Topic_StartFishing(const QJsonObject& topic_data);
private:
    RolePlayer* m_player_;
    QMap<QString, Function_Rsp> map_function_request_;
    QMap<QString, Function_Rsp> map_function_response_;
    QMap<QString, Function_Rsp> map_function_topic_;
};
#endif //DESKXIUXINA_ROLE_MANAGE_H
