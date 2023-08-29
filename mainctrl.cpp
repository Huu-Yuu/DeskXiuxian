#include "mainctrl.h"

MainCtrl::MainCtrl(QObject* parent) : QObject(parent)
{

    //注册MessageHandler(注意要有日志文件夹)
//    qInstallMessageHandler(Logger::OutputMessageHandler);
    data_file_ = DataManage::GetInstance();
    tcp_client_ = new TcpClient;
    main_ui_obj_ = new MainUI;
    logger_obj_ = Logger::GetInstance();
    game_obj_ = GameProgress::GetInstance();
    role_obj_ = RoleSystem::GetInstance();
    role_item_ = ItemSystem::GetInstance();

#if DATABASE_TYPE == 0
    // 初始化UI和角色数据
    InitRoleInfo();
#endif
    // 日志输出
    connect(this, &MainCtrl::SignalLogOut, logger_obj_, &Logger::SlotOutTolog);
    connect(main_ui_obj_, &MainUI::SignalLogOut, logger_obj_, &Logger::SlotOutTolog);

    // 绑定修炼
    connect(game_obj_, &GameProgress::SignaleLifeUpdataTimeOut, role_obj_, &RoleSystem::SlotLifeUpdata);
    connect(game_obj_, &GameProgress::SignalJianghuTimeOut, role_obj_, &RoleSystem::SlotCyclicCultivation);
    connect(game_obj_, &GameProgress::SignalBasicAttTimeOut, role_obj_, &RoleSystem::SlotCyclicEnhanceAtt);
    connect(main_ui_obj_, &MainUI::SignalUpgradeLevel, role_obj_, &RoleSystem::SlotUpgradeLevel);
    connect(main_ui_obj_, &MainUI::SignalStartFishing, this, &MainCtrl::SlotStartFishing);
    connect(main_ui_obj_, &MainUI::SignalStopFishing, this, &MainCtrl::SlotStopFishing);

    // 更新UI
    connect(role_obj_, &RoleSystem::SignalUpdateUI, main_ui_obj_, &MainUI::SlotUpdateUI);
    connect(role_obj_, &RoleSystem::SignalActivateCultivaUpButton, main_ui_obj_, &MainUI::SlotActivateCultivaUpButton);
    connect(role_obj_, &RoleSystem::SignalDisableCultivaUpButton, main_ui_obj_, &MainUI::SlotDisableCultivaUpButton);

    // 保存角色基本信息
    connect(role_obj_, &RoleSystem::SignalUpdateRoleInfoDatabase, data_file_, &DataManage::SlotSaveRoleInfoToDatabase);
    connect(role_obj_, &RoleSystem::SignalUpdateRoleItemDatabase, data_file_, &DataManage::SlotSaveRoleItemToDatabase);
    connect(role_obj_, &RoleSystem::SignalUpdateRoleCoefficientDatabase, data_file_, &DataManage::SlotSaveRoleCoefficientToDatabase);

    // 消息发送到窗口
    connect(role_obj_, &RoleSystem::SignalShowMsgToUI, main_ui_obj_, &MainUI::SlotShowMsg);
    connect(this, &MainCtrl::SignalShowMsgToUI, main_ui_obj_, &MainUI::SlotShowMsg);

#if DATABASE_TYPE == 0
    // 获取本地登录记录，检查是否可以自动登录
    if(!data_file_->AutomaticLogin())
    {
        // 进入登录、注册
        login_obj_->show();
//        modify_obj_->show();
    }
#elif DATABASE_TYPE == 2
    // 初始化角色网络资料
    InitRoleNetworkData();
#endif
}

MainCtrl::~MainCtrl()
{
    if(data_file_ != nullptr)
    {
        delete data_file_;
        data_file_ = nullptr;
    }
    if(main_ui_obj_ != nullptr)
    {
        delete main_ui_obj_;
        main_ui_obj_ = nullptr;
    }
    if(role_obj_ != nullptr)
    {
        delete role_obj_;
        role_obj_ = nullptr;
    }
    if(logger_obj_ != nullptr)
    {
        delete logger_obj_;
        logger_obj_ = nullptr;
    }
    if(game_obj_ != nullptr)
    {
        // 清理游戏进程类 ———————— 线程非安全退出-待处理
        game_obj_->quit();
        game_obj_->wait();
        delete game_obj_;
        game_obj_ = nullptr;
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
    main_ui_obj_->show();
}

void MainCtrl::SlotStartFishing()
{
    game_obj_->StarPractic();
    role_obj_->CheckExpIsUpgrade();
    // 输出角色当前事件系数
    int seconds_info = game_obj_->GetAnecdotesTime() / 1000;
    int seconds_att = game_obj_->GetAttTime() / 1000;
    emit SignalShowMsgToUI(QString("当前基本事件循环周期为：%1秒，属性事件循环周期为：%2秒").arg(seconds_info).arg(seconds_att));

}

void MainCtrl::SlotStopFishing()
{
    game_obj_->StopPractic();
}

void MainCtrl::InitRoleInfo()
{
    // 从数据库获取角色基本信息
    QString last_game_time = "最近一次离线时间是：" + data_file_->GetLastGameTime();
    emit SignalShowMsgToUI(last_game_time);
    QString name = data_file_->GetTableToInfo("RoleInfo", "roleName");
    QString life = data_file_->GetTableToInfo("RoleInfo", "roleLife");
    QString prestige = data_file_->GetTableToInfo("RoleInfo", "rolePrestige");
    QString LV = data_file_->GetTableToInfo("RoleInfo", "roleLv");
    CultivationStage cultivation = static_cast<CultivationStage>(LV.toInt());
    QString cur_exp = data_file_->GetTableToInfo("RoleInfo", "roleCurExp");
    QString exp = data_file_->GetTableToInfo("RoleInfo", "roleExp");
    QString agg = data_file_->GetTableToInfo("RoleInfo", "roleAgg");
    QString def = data_file_->GetTableToInfo("RoleInfo", "roleDef");
    QString hp = data_file_->GetTableToInfo("RoleInfo", "roleHp");

    // 从数据库获取角色获取装备
    QString weapon = data_file_->GetTableToInfo("RoleEquip", "equipWeapon");
    QString magic = data_file_->GetTableToInfo("RoleEquip", "equipMagic");
    QString helmet = data_file_->GetTableToInfo("RoleEquip", "equipHelmet");
    QString clothing = data_file_->GetTableToInfo("RoleEquip", "equipClothing");
    QString britches = data_file_->GetTableToInfo("RoleEquip", "equipBritches");
    QString shoe = data_file_->GetTableToInfo("RoleEquip", "equipShoe");
    QString jewelry = data_file_->GetTableToInfo("RoleEquip", "equipJewelry");
    QString mount = data_file_->GetTableToInfo("RoleEquip", "equipMount");

    // 从数据库获取角色获取物品、道具
    QString money = data_file_->GetTableToInfo("RoleItem", "roleMoney");
    QString rename_card = data_file_->GetTableToInfo("RoleItem", "renameCard");

    // 从数据库获取角色属性相关系数
    QString life_Coefficient = data_file_->GetTableToInfo("RoleCoefficient", "RCLife");
    QString RC_SurviveDisaster = data_file_->GetTableToInfo("RoleCoefficient", "RCSurviveDisaster");

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

    // 更新角各项属性系数
    role_obj_->SetLifeCoefficient(life_Coefficient.toInt());
    role_obj_->SetSurviveDisaster(RC_SurviveDisaster.toInt());

    role_obj_->UpdataMaxRoleLife();     // 更新最大寿命
    role_obj_->UpdateEextGradeEXP();    // 更新升级需要的经验
    role_obj_->CheckExpIsUpgrade();     // 更新是否可以升级

    // 更新UI显示
    main_ui_obj_->UpdateRoleInformation(name, life, prestige, role_obj_->GetCultivationName(cultivation));
    main_ui_obj_->UpdatePhysicalStrength(cur_exp, agg, def, hp);
    main_ui_obj_->UpdateEquip(weapon, magic, helmet, clothing, britches, shoe, jewelry, mount);
}

void MainCtrl::InitRoleNetworkData()
{
    // 账号校验不通过，显示注册页面
    main_ui_obj_->ShowLoginWidget();
    // 账号校验通过，显示运行界面
//    main_ui_obj_->ShowModifyNameWidget();
}

void MainCtrl::SlotDeviceResultDeal(int result, QJsonObject extra)
{
    int error_base = result & ERROR_BASE_MASK;
    switch (error_base)
    {
        case ERROR_NETWORK_BASE:
        {
            switch (result)
            {
                case ERROR_NETWORK_DISCONNECTED:
                {
                    qDebug() << "网络连接断开";
                    break;
                }
                case ERROR_NETWORK_COMMU_REFUSE:
                {
                    qDebug() << "服务器拒绝通信";
                    break;
                }
                case ERROR_NETWORK_REQUEST_REJECT:
                {
                    qDebug() << "服务器拒绝请求";
                    break;
                }
            }
            break;
        }
        default:
        {
            if (result != NO_ERROR)
            {
                qDebug() << Logger::GetErrorInfo(result, 2);
            }
        }
    }
}
