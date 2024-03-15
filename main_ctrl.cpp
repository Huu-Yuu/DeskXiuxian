#include "main_ctrl.h"
#include "modules/item/item_manage.h"
#include "modules/filedata/db_manage.h"
#include "modules/progress/progress_manage.h"
#include "modules/role/role_manage.h"
#include "modules/ui/ui_manage.h"
#include "modules/public/public_declare.h"

MainCtrl::MainCtrl(QObject* parent) : QObject(parent)
{
    //注册MessageHandler(注意要有日志文件夹)
//    qInstallMessageHandler(Logger::OutputMessageHandler);
    data_file_ = DataService::getInstance();
    main_ui_obj_ = MainUI::getInstance();
    logger_obj_ = Logger::getInstance();
    game_obj_ = ProgressService::getInstance();
    role_obj_ = RolePlayer::getInstance();
    role_item_ = ItemService::getInstance();
    InitObj();
    InitConnect();
    InitFun();

#if DATABASE_TYPE == 0
    // 获取本地登录记录，检查是否可以自动登录
    if(data_file_->AutomaticLogin())
    {
        qDebug() << "自动登录，获取角色数据";
        SlotInitRoleData();
        main_ui_obj_->show();
    }
    else
    {
        // 进入登录、注册界面
        main_ui_obj_->ShowLoginWidget();
    }
#elif DATABASE_TYPE == 1
    // 初始化UI和角色数据
    InitRoleInfo();
#elif DATABASE_TYPE == 2
    // 初始化角色网络资料
    InitRoleNetworkData();
#endif
    // 日志输出
    connect(this, &MainCtrl::SignalLogOut, logger_obj_, &Logger::SlotOutTolog);
    connect(main_ui_obj_, &MainUI::SignalLogOut, logger_obj_, &Logger::SlotOutTolog);

    // 绑定修炼
    connect(game_obj_, &ProgressService::SignaleLifeUpdataTimeOut, role_obj_, &RolePlayer::SlotLifeUpdate);
    connect(game_obj_, &ProgressService::SignalJianghuTimeOut, role_obj_, &RolePlayer::SlotCyclicCultivation);
    connect(game_obj_, &ProgressService::SignalBasicAttTimeOut, role_obj_, &RolePlayer::SlotCyclicEnhanceAtt);
    connect(main_ui_obj_, &MainUI::SignalUpgradeLevel, role_obj_, &RolePlayer::SlotUpgradeLevel);
    connect(main_ui_obj_, &MainUI::SignalStartFishing, this, &MainCtrl::SlotStartFishing);
    connect(main_ui_obj_, &MainUI::SignalStopFishing, this, &MainCtrl::SlotStopFishing);

    // 更新UI
    connect(role_obj_, &RolePlayer::SignalUpdateUI, main_ui_obj_, &MainUI::SlotUpdateUI);
    connect(role_obj_, &RolePlayer::SignalActivateCultivaUpButton, main_ui_obj_, &MainUI::SlotActivateCultivaUpButton);
    connect(role_obj_, &RolePlayer::SignalDisableCultivaUpButton, main_ui_obj_, &MainUI::SlotDisableCultivaUpButton);
    connect(main_ui_obj_, &MainUI::SignalInitRoleData, this, &MainCtrl::SlotInitRoleData);

    // 保存角色基本信息
    connect(role_obj_, &RolePlayer::SignalUpdateRoleInfoDatabase, data_file_, &DataService::SlotSaveRoleInfoToDatabase);
    connect(role_obj_, &RolePlayer::SignalUpdateRoleItemDatabase, data_file_, &DataService::SlotSaveRoleItemToDatabase);
    connect(role_obj_, &RolePlayer::SignalUpdateEquipItemDatabase, data_file_, &DataService::SlotSaveRoleEquipToDatabase);
    connect(role_obj_, &RolePlayer::SignalUpdateRoleCoefficientDatabase, data_file_, &DataService::SlotSaveRoleCoefficientToDatabase);

    // 消息发送到窗口
    connect(role_obj_, &RolePlayer::SignalShowMsgToUI, main_ui_obj_, &MainUI::SlotShowMsg);
    connect(this, &MainCtrl::SignalShowMsgToUI, main_ui_obj_, &MainUI::SlotShowMsg);
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

void MainCtrl::SlotInitRoleData()
{
    QJsonObject role_info_data = data_file_->GetRemoteRoleInfo();
    QJsonObject role_rc_data = data_file_->GetRemoteRoleRC();
    QJsonObject role_equip_data = data_file_->GetRemoteRoleEquip();
    QJsonObject role_item_data = data_file_->GetRemoteRoleItem();
    // 更新UI
    main_ui_obj_->InitRoleUI(role_info_data, role_item_data, role_rc_data, role_equip_data);
    // 更新角色基本信息
    int cultivation = role_info_data.value("role_lv").toString().toInt();
    role_obj_->SetRoleName(role_info_data.value("role_name").toString());
    role_obj_->SetRoleLife(role_info_data.value("role_life").toString().toInt());
    role_obj_->SetRoleBaseAtt(kRolePrestigeAtt, role_info_data.value("role_prestige").toString().toInt());
    role_obj_->SetRoleBaseAtt(kRoleLvAtt, cultivation);
    role_obj_->SetRoleBaseAtt(kRoleExpAtt, role_info_data.value("role_cur_exp").toString().toInt());
    role_obj_->SetRoleBaseAtt(kRoleMaxExpAtt, role_info_data.value("role_exp").toString().toInt());
    role_obj_->SetRoleBaseAtt(kRoleAggAtt, role_info_data.value("role_agg").toString().toInt());
    role_obj_->SetRoleBaseAtt(kRoleDefAtt, role_info_data.value("role_def").toString().toInt());
    role_obj_->SetRoleBaseAtt(kRoleHpAtt, role_info_data.value("role_hp").toString().toInt());
    // 更新装备
//    role_obj_->SetEquipWeapon();
//    role_obj_->SetEquipMagic();
//    role_obj_->SetEquipHelmet();
//    role_obj_->SetEquipClothing();
//    role_obj_->SetEquipBritches();
//    role_obj_->SetEquipShoe();
//    role_obj_->SetEquipJewelry();
    // 更新角色道具
    role_item_->SetItemMoney(role_item_data.value("role_money").toString().toInt());
//    role_item_->SetItemRenameCard(role_item_data_.value("role_money").toString().toInt());

    // 更新角各项属性系数
    role_obj_->SetLifeCoefficient(role_rc_data.value("rc_life").toString().toInt());
    role_obj_->SetSurviveDisaster(role_rc_data.value("rc_survive_disaster").toString().toInt());

    role_obj_->UpdataMaxRoleLife();     // 更新最大寿命
    role_obj_->UpdateEextGradeEXP();    // 更新升级需要的经验
    role_obj_->CheckExpIsUpgrade();     // 更新是否可以升级
}

void MainCtrl::SlotStopFishing()
{
    game_obj_->StopPractic();
}

void MainCtrl::InitRoleInfo()
{
    QJsonObject pub_data;
    pub_data.insert("type", mainCmd::InitRoleInfo);
    pub_data.insert("data", QJsonObject());
    onPubTopic(pub_data);

    // 从数据库获取角色基本信息
    QString last_game_time = "最近一次离线时间是：" + data_file_->GetLastGameTime();
    emit SignalShowMsgToUI(last_game_time);
    QString name = data_file_->GetTableToInfo("RoleInfo", "roleName");
    QString life = data_file_->GetTableToInfo("RoleInfo", "roleLife");
    QString max_life = data_file_->GetTableToInfo("RoleInfo", "roleMaxLife");
    QString prestige = data_file_->GetTableToInfo("RoleInfo", "rolePrestige");
    QString LV = data_file_->GetTableToInfo("RoleInfo", "roleLv");
    int cultivation = LV.toInt();
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
    QString money = data_file_->GetTableToInfo("RoleItemEnum", "roleMoney");

    // 从数据库获取角色属性相关系数
    QString life_Coefficient = data_file_->GetTableToInfo("RoleCoefficient", "RCLife");
    QString RC_SurviveDisaster = data_file_->GetTableToInfo("RoleCoefficient", "RCSurviveDisaster");

    // 将获取到的值赋值给对象
    role_obj_->SetRoleName(name);
    role_obj_->SetRoleLife(life.toUInt());
    role_obj_->SetRoleBaseAtt(kRoleMaxLifeAtt, max_life.toInt());
    role_obj_->SetRoleBaseAtt(kRolePrestigeAtt, prestige.toInt());
    role_obj_->SetRoleBaseAtt(kRoleLvAtt, cultivation);
    role_obj_->SetRoleBaseAtt(kRoleExpAtt, cur_exp.toInt());
    role_obj_->SetRoleBaseAtt(kRoleMaxExpAtt, exp.toInt());
    role_obj_->SetRoleBaseAtt(kRoleAggAtt, agg.toInt());
    role_obj_->SetRoleBaseAtt(kRoleDefAtt, def.toInt());
    role_obj_->SetRoleBaseAtt(kRoleHpAtt, hp.toInt());
    role_obj_->SetEquipAreaName(kWeaponArea, weapon);
    role_obj_->SetEquipAreaName(kMagicArea, magic);
    role_obj_->SetEquipAreaName(kHelmetArea, helmet);
    role_obj_->SetEquipAreaName(kClothingArea, clothing);
    role_obj_->SetEquipAreaName(kBritchesArea, britches);
    role_obj_->SetEquipAreaName(kShoeArea, shoe);
    role_obj_->SetEquipAreaName(kJewelrArea, jewelry);

    // 更新角色道具
    role_item_->SetItemMoney(money.toInt());
//    role_item_->SetItemRenameCard(rename_card.toInt());

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
    qDebug() << "客户端信号错误处理函数，附加信息为：" << extra;
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

void MainCtrl::InitObj() {
    QSharedPointer<InterfaceManager> interface_manager;
    interface_manager.reset(new ItemManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
    interface_manager.reset(new DBManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
    interface_manager.reset(new ProgressManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
    interface_manager.reset(new RoleManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
    interface_manager.reset(new UIManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
}

void MainCtrl::RegisterInterfaceManager(QString type, QSharedPointer<InterfaceManager> inter_ptr) {
    if(m_manager_map.contains(type))
    {
        qDebug() << "已存在类型" << type << ",跳过注册请求";
    }
    else
    {
        qDebug() << "注册类型" << type << inter_ptr << "请求";
        m_manager_map.insert(type, inter_ptr);
    }
}

void MainCtrl::InitConnect() {
    QMapIterator < QString, QSharedPointer<InterfaceManager> > itor(m_manager_map);
    while(itor.hasNext())
    {
        itor.next();
        connect(itor.value().data(), &InterfaceManager::SignalActionRequest,
                this, &MainCtrl::onActionRequest);
        connect(itor.value().data(), &InterfaceManager::SignalActionResponse,
                this, &MainCtrl::onActionResponse);
        connect(itor.value().data(), &InterfaceManager::SignalSubTopic,
                this, &MainCtrl::onSubTopic);
        connect(itor.value().data(), &InterfaceManager::SignalPubTopic,
                this, &MainCtrl::onPubTopic);
        connect(this, &MainCtrl::SignalActionRequestResult,
                itor.value().data(), &InterfaceManager::SlotActionResponse);
    }
}

void MainCtrl::onPubTopic(const QJsonObject &request_data) {
    QString type = request_data.value("type").toString();
    QMap<QString, QStringList>::iterator it = m_cmd_topic_listen_list.begin();
    for(; it != m_cmd_topic_listen_list.end(); ++it)
    {
        if(it.value().contains(type) && m_manager_map.contains(it.key()))
        {
            m_manager_map[it.key()]->SlotPubTopic(request_data);
        }
    }
}

void MainCtrl::onSubTopic(TopicSubActionType action_type, const QStringList &topic_list) {
    InterfaceManager* psender = qobject_cast<InterfaceManager*>(sender());

    QString topic_msg;
    for(int i = 0; i < topic_list.size(); i++)
    {
        topic_msg += ("," + topic_list[i]);
    }
    QString debug_msg = "";
    if(action_type == TopicSubActionType::kSubType)
    {
        debug_msg = "注册";
    }
    else if(action_type == TopicSubActionType::kUnsubType)
    {
        debug_msg = "取消注册";
    }

    if(psender != nullptr)
    {
        QString module_name = psender->GetModuleName();
        if(action_type == TopicSubActionType::kSubType)
        {
            m_cmd_topic_listen_list[module_name].append(topic_list);
        }
        else if(action_type == TopicSubActionType::kUnsubType)
        {
            for(int i = 0; i < topic_list.size(); i++)
            {
                m_cmd_topic_listen_list[module_name].removeAll(topic_list.at(i));
            }
        }
    }
    else
    {
        LOG_DEBUG(kMainCtrl, QString("无法处理订阅请求:模块未初始化，%1主动上报消息：%2").arg(debug_msg).arg(topic_msg));
    }
}

void MainCtrl::InitFun() {
    QMapIterator < QString, QSharedPointer<InterfaceManager> > itor(m_manager_map);
    while(itor.hasNext())
    {
        itor.next();
        itor.value().data()->Init();
    }
}

void MainCtrl::onActionRequest(const QJsonObject &request_data) {
    QString type = request_data.value("type").toString();
    QString dest = request_data.value("dest").toString();
    QString ori = request_data.value("ori").toString();
    LOG_DEBUG(kMainCtrl, QString("主控类收到请求：%1 -> %2").arg(sender()->objectName()).arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    if(m_manager_map.contains(dest))
    {
        m_manager_map[dest]->SlotActionRequest(request_data);
    }
    else
    {
        LOG_DEBUG(kMainCtrl, QString("[main] 无法处理请求：%1").arg(type));
    }
}

void MainCtrl::onActionResponse(const QJsonObject &request_data) {
    QString type = request_data.value("type").toString();
    QString dest = request_data.value("dest").toString();
    LOG_DEBUG(kMainCtrl, QString("中心回复请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    if(m_manager_map.contains(dest))
    {
        m_manager_map[dest]->SlotActionResponse(request_data);
    }
    else
    {
        LOG_DEBUG(kMainCtrl, QString("[main] 无法处理回复：%1").arg(type));
    }
}
