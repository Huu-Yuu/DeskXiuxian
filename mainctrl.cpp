#include "mainctrl.h"

MainCtrl::MainCtrl(QObject *parent) : QObject(parent)
{
    ui_obj_ = new MainUI;
    role_obj_ = RoleSystem::GetInstance();
    logger_obj_ = Logger::GetInstance();
    data_file_ = DataManage::GetInstance();
    game_obj_ = GameProgress::GetInstance();

    // 初始化UI和角色数据
    InitRoleInfo();

    connect(this,&MainCtrl::SignalLogOut,logger_obj_,&Logger::SlotOutTolog);

    // 绑定修炼
    connect(game_obj_, &GameProgress::SignalJianghuTimeOut, role_obj_, &RoleSystem::SlotCyclicCultivation);
    // 更新UI
    connect(role_obj_, &RoleSystem::SignalUpdateUI, ui_obj_, &MainUI::SlotUpdateUI);
    // 保存角色基本信息
    connect(role_obj_, &RoleSystem::SignalUpdateRoleInfoDatabase, data_file_, &DataManage::SlotSaveRoleInfoToDatabase);

    // 消息发生到窗口
    connect(role_obj_, &RoleSystem::SignalShowMsgToUI, ui_obj_, &MainUI::SlotShowMsg);
}

MainCtrl::~MainCtrl()
{
    if(data_file_ != NULL)
    {
        delete data_file_;
        data_file_ = NULL;
    }
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
    if(game_obj_ != NULL)
    {
        delete game_obj_;
        game_obj_ = NULL;
    }

}

void MainCtrl::DebugOutToLog(QString msg)
{
    emit SignalLogOut(QtDebugMsg, QMessageLogContext(), msg);
}

void MainCtrl::StartFishing()
{
    // 开始倒计时：
    game_obj_->start();

}
void MainCtrl::ShowMainUi()
{
    ui_obj_->show();
}

void MainCtrl::InitRoleInfo()
{
    QString last_game_time = "最近一次离线时间是：" + data_file_->GetLastGameTime();
    ui_obj_->AddMessage(last_game_time);
    QString name = data_file_->GetTableToInfo("RoleInfo","roleName");
    QString life = data_file_->GetTableToInfo("RoleInfo","roleLife");
    QString prestige = data_file_->GetTableToInfo("RoleInfo","rolePrestige");
    QString cultivation = data_file_->GetTableToInfo("RoleInfo","roleCultivation");

    QString exp = data_file_->GetTableToInfo("RoleInfo","roleExp");
    QString agg = data_file_->GetTableToInfo("RoleInfo","roleAgg");
    QString def = data_file_->GetTableToInfo("RoleInfo","roleDef");
    QString hp = data_file_->GetTableToInfo("RoleInfo","roleHp");

    QString weapon = data_file_->GetTableToInfo("RoleEquip","equipWeapon");
    QString magic = data_file_->GetTableToInfo("RoleEquip","equipMagic");
    QString helmet = data_file_->GetTableToInfo("RoleEquip","equipHelmet");
    QString clothing = data_file_->GetTableToInfo("RoleEquip","equipClothing");
    QString britches = data_file_->GetTableToInfo("RoleEquip","equipBritches");
    QString shoe = data_file_->GetTableToInfo("RoleEquip","equipShoe");
    QString jewelry = data_file_->GetTableToInfo("RoleEquip","equipJewelry");

    role_obj_->SetRoleName(name);
    role_obj_->SetRoleLife(life.toUInt());
    role_obj_->SetRolePrestige(prestige.toInt());
    role_obj_->SetRoleCultivation(cultivation);
    role_obj_->SetRoleExp(exp.toInt());
    role_obj_->SetRoleAgg(agg.toInt());
    role_obj_->SetRoleDef(def.toInt());
    role_obj_->SetRoleHp(hp.toInt());
    role_obj_->SetEquipWeapon(weapon);
    role_obj_->SetEquipMagic(magic);
    role_obj_->SetEquipHelmet(helmet);
    role_obj_->SetEquipClothing(clothing);
    role_obj_->SetEquipBritches(britches);
    role_obj_->SetEquipShoe(shoe);
    role_obj_->SetEquipJewelry(jewelry);

    ui_obj_->UpdateRoleInformation(name, life, prestige, cultivation);
    ui_obj_->UpdatePhysicalStrength(exp, agg, def, hp);
    ui_obj_->UpdateEquip(weapon, magic, helmet, clothing, britches, shoe, jewelry);
}
