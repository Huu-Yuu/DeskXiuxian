//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_ROLE_SYSTEM_H
#define DESKXIUXINA_ROLE_SYSTEM_H
#include <QObject>
#include "modules/interface_manager.h"
#include "role_player.h"

class RoleSystem : public InterfaceManager
{
    Q_OBJECT
public:
    RoleSystem();
    ~RoleSystem();
    int Init() override;

public slots:
    void SlotActionResponse(const QJsonObject& request_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& status) override;

    void SlotQuantityChanged(RoleItemEnum item_enum , int sum); ///< 物品数量被改变槽函数，物品枚举，变更后的数量
private:
    RolePlayer* role_obj_;
};
#endif //DESKXIUXINA_ROLE_SYSTEM_H
