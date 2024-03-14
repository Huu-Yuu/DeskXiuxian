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

public slots:
    void SlotActionResponse(const QJsonObject& request_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& status) override;

private:
    RolePlayer* role_obj_;
};
#endif //DESKXIUXINA_ROLE_MANAGE_H
