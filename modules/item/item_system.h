//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_ITEM_SYSTEM_H
#define DESKXIUXINA_ITEM_SYSTEM_H
#include <QObject>
#include "modules/interface_manager.h"
#include "item_manage.h"

class ItemSystem : public InterfaceManager
{
    Q_OBJECT
public:
    ItemSystem();
    ~ItemSystem();
private:
    ItemManage* item_obj_;
};

#endif //DESKXIUXINA_ITEM_SYSTEM_H
