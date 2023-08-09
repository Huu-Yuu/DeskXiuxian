#include "mainctrl.h"

MainCtrl::MainCtrl(QObject *parent) : QObject(parent)
{
    ui_obj_ = new MainUI;
    role_obj_ = RoleSystem::GetInstance();
    logger_obj_ = Logger::GetInstance();
    data_file_ = DataManage::GetInstance();
    game_obj_ = GameProgress::GetInstance();
    role_item_ = ItemSystem::GetInstance();

    // 初始化UI和角色数据
    InitRoleInfo();

    connect(this,&MainCtrl::SignalLogOut,logger_obj_,&Logger::SlotOutTolog);

    // 绑定修炼
    connect(game_obj_, &GameProgress::SignalJianghuTimeOut, role_obj_, &RoleSystem::SlotCyclicCultivation);
    // 更新UI
    connect(role_obj_, &RoleSystem::SignalUpdateUI, ui_obj_, &MainUI::SlotUpdateUI);

    // 保存角色基本信息
    connect(role_obj_, &RoleSystem::SignalUpdateRoleInfoDatabase, data_file_, &DataManage::SlotSaveRoleInfoToDatabase);
    connect(role_obj_, &RoleSystem::SignalUpdateRoleItemDatabase, data_file_, &DataManage::SlotSaveRoleItemToDatabase);

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
        // 清理游戏进程类 ———————— 线程非安全退出-待处理
        game_obj_->quit();
        game_obj_->wait();
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
    // 从数据库获取角色基本信息
    QString last_game_time = "最近一次离线时间是：" + data_file_->GetLastGameTime();
    ui_obj_->AddMessage(last_game_time);
    QString name = data_file_->GetTableToInfo("RoleInfo","roleName");
    QString life = data_file_->GetTableToInfo("RoleInfo","roleLife");
    QString prestige = data_file_->GetTableToInfo("RoleInfo","rolePrestige");
    QString LV = data_file_->GetTableToInfo("RoleInfo","roleLv");
    CultivationStage cultivation = static_cast<CultivationStage>(LV.toInt());

    QString cur_exp = data_file_->GetTableToInfo("RoleInfo","roleCurExp");
    QString exp = data_file_->GetTableToInfo("RoleInfo","roleExp");
    QString agg = data_file_->GetTableToInfo("RoleInfo","roleAgg");
    QString def = data_file_->GetTableToInfo("RoleInfo","roleDef");
    QString hp = data_file_->GetTableToInfo("RoleInfo","roleHp");

    // 从数据库获取角色获取装备
    QString weapon = data_file_->GetTableToInfo("RoleEquip","equipWeapon");
    QString magic = data_file_->GetTableToInfo("RoleEquip","equipMagic");
    QString helmet = data_file_->GetTableToInfo("RoleEquip","equipHelmet");
    QString clothing = data_file_->GetTableToInfo("RoleEquip","equipClothing");
    QString britches = data_file_->GetTableToInfo("RoleEquip","equipBritches");
    QString shoe = data_file_->GetTableToInfo("RoleEquip","equipShoe");
    QString jewelry = data_file_->GetTableToInfo("RoleEquip","equipJewelry");

    // 从数据库获取角色获取物品、道具
    QString money = data_file_->GetTableToInfo("RoleItem","roleMoney");
    QString rename_card = data_file_->GetTableToInfo("RoleItem","renameCard");



    // 将获取到的值赋值给对象
    role_obj_->SetRoleName(name);
    role_obj_->SetRoleLife(life.toUInt());
    role_obj_->SetRolePrestige(prestige.toInt());
    role_obj_->SetRoleCultivation(cultivation);
    role_obj_->SetCurRoleExp(cur_exp.toInt());
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

    // 更新角色道具
    role_item_->SetItemMoney(money.toInt());
    role_item_->SetItemRenameCard(rename_card.toInt());

    // 更新UI显示
    ui_obj_->UpdateRoleInformation(name, life, prestige, role_obj_->GetCultivationName(cultivation));
    ui_obj_->UpdatePhysicalStrength(cur_exp, agg, def, hp);
    ui_obj_->UpdateEquip(weapon, magic, helmet, clothing, britches, shoe, jewelry);
}
