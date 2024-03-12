#ifndef DESKXIUXINA_UI_SYSTEM_H
#define DESKXIUXINA_UI_SYSTEM_H

#include <QObject>
#include "modules/interface_manager.h"
#include "mainui.h"
class UISystem : public InterfaceManager
{
    Q_OBJECT
public:
    UISystem();
    ~UISystem();
private:
    MainUI* ui_obj_;
};


#endif //DESKXIUXINA_UI_SYSTEM_H
