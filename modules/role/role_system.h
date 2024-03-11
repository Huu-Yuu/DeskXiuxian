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
private:
    RolePlayer* role_obj_;
};
#endif //DESKXIUXINA_ROLE_SYSTEM_H
