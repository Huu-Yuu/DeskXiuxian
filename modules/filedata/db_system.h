//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_DB_SYSTEM_H
#define DESKXIUXINA_DB_SYSTEM_H
#include <QObject>
#include "modules/interface_manager.h"
#include "data_manage.h"

class DBSystem : public InterfaceManager
{
    Q_OBJECT
public:
    DBSystem();
    ~DBSystem();
private:
    DataManage* data_obj_;
};

#endif //DESKXIUXINA_DB_SYSTEM_H
