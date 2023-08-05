#ifndef MAINCTRL_H
#define MAINCTRL_H

#include <QObject>
#include "mainui.h"
#include "cultivation/cultivationsystem.h"
#include "role/rolesystem.h"
#include "logger/logger.h"
#include "filedata/datamanage.h"


class MainCtrl : public QObject
{
    Q_OBJECT
public:
    explicit MainCtrl(QObject *parent = nullptr);

    void Init();

private:
    MainUI * ui_obj_;
    RoleSystem * role_obj_;
    Logger * logge_objr_;
    CultivationSystem * cul_obj_;
    DataManage *data_file_;
};

#endif // MAINCTRL_H
