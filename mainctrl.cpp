#include "mainctrl.h"

MainCtrl::MainCtrl(QObject *parent) : QObject(parent)
{
    ui_obj_ = new MainUI;
    role_obj_ = RoleSystem::GetInstance();
    logger_obj_ = Logger::GetInstance();
    cul_obj_ = new CultivationSystem;
    data_file_ = DataManage::GetInstance();

    InitRoleInfo();

    connect(this,&MainCtrl::SignalLogOut,logger_obj_,&Logger::SlotOutTolog);
}

MainCtrl::~MainCtrl()
{
    if(ui_obj_ != NULL)
    {
        delete ui_obj_;
        ui_obj_ = NULL;
    }
    if(role_obj_ !=NULL)
    {
        delete role_obj_;
        role_obj_ = NULL;
    }
    if(logger_obj_ != NULL)
    {
        delete logger_obj_;
        logger_obj_ = NULL;
    }
    if(cul_obj_ != NULL)
    {
        delete cul_obj_;
        cul_obj_ = NULL;
    }
    if(data_file_ != NULL)
    {
        delete data_file_;
        data_file_ = NULL;
    }
}

void MainCtrl::DebugOutToLog(QString msg)
{
    emit SignalLogOut(QtDebugMsg, QMessageLogContext(), msg);
}

void MainCtrl::Init()
{
    // 初始化UI数值

}
void MainCtrl::ShowMainUi()
{
    ui_obj_->show();
}

void MainCtrl::InitRoleInfo()
{
    QString last_game_time = "最近一次离线时间是：" + data_file_->GetLastGameTime();
    ui_obj_->AddMessage(last_game_time);
    ui_obj_->UpdateRoleInformation(data_file_->GetTableToInfo("RoleInfo","roleName"),
                                   data_file_->GetTableToInfo("RoleInfo","roleLife"),
                                   data_file_->GetTableToInfo("RoleInfo","rolePrestige"),
                                   data_file_->GetTableToInfo("RoleInfo","roleCultivation"));
    ui_obj_->UpdatePhysicalStrength(data_file_->GetTableToInfo("RoleInfo","roleExp"),
                                    data_file_->GetTableToInfo("RoleInfo","roleAgg"),
                                    data_file_->GetTableToInfo("RoleInfo","roleDef"),
                                    data_file_->GetTableToInfo("RoleInfo","roleHp"));
    ui_obj_->UpdateEquip(data_file_->GetTableToInfo("RoleEquip","equipWeapon"),
                         data_file_->GetTableToInfo("RoleEquip","equipMagic"),
                         data_file_->GetTableToInfo("RoleEquip","equipHelmet"),
                         data_file_->GetTableToInfo("RoleEquip","equipClothing"),
                         data_file_->GetTableToInfo("RoleEquip","equipBritches"),
                         data_file_->GetTableToInfo("RoleEquip","equipShoe"),
                         data_file_->GetTableToInfo("RoleEquip","equipJewelry"));
}
