#include "mainui.h"
#include "ui_mainui.h"
#include "modules/public/public_declare.h"
#include <QJsonArray>
#include <QMenu>
#include <QListWidgetItem>

MainUI::MainUI(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);
    // 初始化成员变量
    logger_obj_ = Logger::getInstance();
    login_obj_ = new LoginWindow;
    modify_obj_ = new ModifyRoleName;
    process = new QProcess;
    m_qmladapter = new QmlAdapter;
    connect(this, &MainUI::SignalLogOut, logger_obj_, &Logger::SlotOutTolog);
    connect(login_obj_, &LoginWindow::SignalLoginSuccessful, this, &MainUI::SlotLoginSuccessful);
    connect(login_obj_, &LoginWindow::SignalActionRequest, this, &MainUI::SignalActionRequest);
    connect(login_obj_, &LoginWindow::SignalActionResponse, this, &MainUI::SignalActionResponse);
    connect(login_obj_, &LoginWindow::SignalPubTopic, this, &MainUI::SignalPubTopic);
    connect(modify_obj_, &ModifyRoleName::SignalRenameSuccessful, this, &MainUI::SlotRenameSuccessful);
    connect(modify_obj_, &ModifyRoleName::SignalActionRequest, this, &MainUI::SignalActionRequest);
    connect(modify_obj_, &ModifyRoleName::SignalActionResponse, this, &MainUI::SignalActionResponse);
    connect(modify_obj_, &ModifyRoleName::SignalPubTopic, this, &MainUI::SignalPubTopic);


    // 初始化UI设置
    // 设置logo
    setWindowIcon(QIcon(":/res/logo.jpg"));

    // 设置窗口标题
    setWindowTitle("桌面修仙");

    // 固定窗口
    setFixedSize(width(), height());

    // 将窗口居中显示
    QRect availableGeometry = QGuiApplication::screens().at(0)->availableGeometry();
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            availableGeometry
        )
    );

    //外层widget布局
    ui->centralwidget->setLayout(ui->outerLayout);

    //主角选项卡布局
    ui->role_page->setLayout(ui->role_Layout);
    ui->role_item->setLayout(ui->package_Layout);
    ui->bisic_Att_Box->setLayout(ui->bisic_Layout);
    ui->equipment_Box->setLayout(ui->equipment_Layout);

    //道具选项卡布局
    ui->item_equip->setLayout(ui->item_equip_Layout);
    ui->item_prop->setLayout(ui->item_prop_Layout);
    ui->item_special->setLayout(ui->item_special_Layout);
    ui->item_material->setLayout(ui->item_material_Layout);
    ui->item_prop_list->setContextMenuPolicy(Qt::CustomContextMenu);

    //商店选项卡布局
    ui->store_equip->setLayout(ui->store_equip_Layout);
    ui->store_prop->setLayout(ui->store_prop_Layout);
    ui->store_special->setLayout(ui->store_special_Layout);
    ui->store_material->setLayout(ui->store_material_Layout);

    // 系统消息选项卡布局
    ui->sys_news_tab->setLayout(ui->sys_news_Layout);
    ui->sys_news_list->setContextMenuPolicy(Qt::CustomContextMenu);

    //世界聊天布局
    ui->world_news_tab->setLayout(ui->world_news_Layout);
    ui->world_news_list->setContextMenuPolicy(Qt::CustomContextMenu);

    //宗门聊天布局
    ui->team_news_tab->setLayout(ui->team_news_Layout);
    ui->team_news_list->setContextMenuPolicy(Qt::CustomContextMenu);


    //道术选项卡布局
    ui->role_skill->setLayout(ui->role_skill_Layout);


    QString date_time_str = QString("%1 %2").arg(__DATE__).arg(__TIME__);
    if (date_time_str.contains("  "))
    {
        date_time_str.replace("  ", " ");
    }
    QDateTime compile_data_time = QLocale(QLocale::English)
            .toDateTime(date_time_str, "MMM d yyyy hh:mm:ss");
    QString compile_time = compile_data_time.toString("yyyy.MM.dd hh:mm:ss");
    QString msg = QString("当前游戏版本为：%1\n发布日期：%2").arg(GAME_VISION).arg(compile_time);
    AddMessage(msg);
}

MainUI::~MainUI()
{
    delete ui;
}

void MainUI::closeEvent(QCloseEvent* event)
{
    qDebug() << "检测到手动关闭游戏，强制结束进程";
    // 打印到日志
    emit SignalLogOut( QtFatalMsg, QMessageLogContext(), "检测到手动关闭游戏，强制结束进程");
    RequestOutside(dbCmd::UpdateLastLoginTime, module_name::data);
    AddMessage("正在退出仙界");
    QTimer::singleShot(2000, this, [event, this]{
        // 杀死所有进程
        QString command = "taskkill /F /IM DeskXiuxian.exe";
        process->start(command);
        process->waitForFinished();

        QMainWindow::closeEvent(event);
    });

}

void MainUI::AddMessage(QString msg)
{
    QString time_stamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm:ss");

    QString display_text = time_stamp + "：" + msg;

    ui->sys_news_list->addItem(display_text);
    // 滚动到底部
    ui->sys_news_list->scrollToBottom();
    // 将消息记录到日志
    emit SignalLogOut(QtInfoMsg, QMessageLogContext(), msg);
}

//Ui::MainUI* MainUI::GetUI()
//{
//    return ui;
//}

void MainUI::InitRoleUI(QJsonObject role_info_data, QJsonObject role_item_data, QJsonObject role_rc_data, QJsonObject role_equic_data)
{
    // 显示角色基本信息
    ui->role_name->setText(role_info_data.value("role_name").toString());
    ui->role_life->setText(role_info_data.value("role_life").toVariant().toString());
    ui->role_prestige->setText(role_info_data.value("role_prestige").toVariant().toString());
    QString lv_name = RolePlayer::GetCultivationName(role_info_data.value("role_lv").toVariant().toInt());
    ui->role_cultivation->setText(lv_name);
    ui->role_exp->setText(role_info_data.value("role_cur_exp").toVariant().toString());
    ui->role_agg->setText(role_info_data.value("role_agg").toVariant().toString());
    ui->role_def->setText(role_info_data.value("role_def").toVariant().toString());
    ui->role_hp->setText(role_info_data.value("role_hp").toVariant().toString());
    // 显示角色物品
    role_item_data = QJsonObject();
    // 显示角色成长系数
    role_rc_data = QJsonObject();
    // 显示角色装备
    role_equic_data = QJsonObject();
}

void MainUI::UpdateRoleInformation(QString name, QString life, QString prestige, QString cultivation)
{
    ui->role_name->setText(name);
    ui->role_life->setText(life);
    ui->role_prestige->setText(prestige);
    ui->role_cultivation->setText(cultivation);
}

void MainUI::UpdatePhysicalStrength(QString exp, QString agg, QString def, QString hp)
{
    ui->role_exp->setText(exp);
    ui->role_agg->setText(agg);
    ui->role_def->setText(def);
    ui->role_hp->setText(hp);
}

void MainUI::UpdateEquip(QString weapon, QString magic, QString helmet, QString clothing,
                         QString britches, QString shoe, QString jewelrt, QString mount, QString title)
{
    ui->equip_weapon->setText(weapon);
    ui->equip_magic->setText(magic);
    ui->equip_helmet->setText(helmet);
    ui->equip_clothing->setText(clothing);
    ui->equip_britches->setText(britches);
    ui->equip_shoe->setText(shoe);
    ui->equip_jewelry->setText(jewelrt);
    ui->equip_mount->setText(mount);
    ui->role_title->setText(title);

}

void MainUI::SlotUpdateUI(RoleUIEnum part, QString new_data)
{
    switch (part)
    {
        case kUnknown:
            break;
        case kRoleName:
            ui->role_name->setText(new_data);
            break;
        case kRoleLife:
            ui->role_life->setText(new_data);
            break;
        case kRolePrestige:
            ui->role_prestige->setText(new_data);
            break;
        case kRoleCultivation:
            ui->role_cultivation->setText(new_data);
            break;
        case kRoleExp:
            ui->role_exp->setText(new_data);
            break;
        case kRoleAgg:
            ui->role_agg->setText(new_data);
            break;
        case kRoleDef:
            ui->role_def->setText(new_data);
            break;
        case kRoleHp:
            ui->role_hp->setText(new_data);
            break;
        case kAttMetal:
        case kAttWood:
        case kAttWater:
        case kAttFire:
        case kAttEarth:
            break;
        case kEquipWeapon:
            ui->equip_weapon->setText(new_data);
            break;
        case kEquipMagic:
            ui->equip_magic->setText(new_data);
            break;
        case kEquipHelmet:
            ui->equip_helmet->setText(new_data);
            break;
        case kEquipClothing:
            ui->equip_clothing->setText(new_data);
            break;
        case kEquipBritches:
            ui->equip_britches->setText(new_data);
            break;
        case kEquipShoe:
            ui->equip_shoe->setText(new_data);
            break;
        case kEquipJewelrt:
            ui->equip_jewelry->setText(new_data);
            break;
        case kEquipeMount:
            ui->equip_mount->setText(new_data);
            break;
        case kEquipeTitle:
            ui->role_title->setText(new_data);
    }
}

void MainUI::SlotActivateCultivaUpButton()
{
    if(!ui->cultiva_up_but->isEnabled())
    {
        ui->cultiva_up_but->setEnabled(true);
        QString msg = "修为已到达瓶颈，请准备突破！";
        AddMessage(msg);
    }
}

void MainUI::SlotDisableCultivaUpButton()
{
    if(ui->cultiva_up_but->isEnabled())
    {
        ui->cultiva_up_but->setEnabled(false);
    }
}

void MainUI::SlotShowMsg(QString msg)
{
    AddMessage(msg);
}

void MainUI::SlotLoginSuccessful()
{
    CloseLoginWidget();
    emit SignalLogOut(QtInfoMsg, QMessageLogContext(), "正在检查是否首次登录");
    RequestOutside(dbCmd::CheckLoginFist, module_name::data);
}

void MainUI::SlotRenameSuccessful(QString name)
{
    CloseModifyNameWidget();
    if(!isVisible())
    {
        RequestOutside(mainCmd::InitRemoteRoleInfo, module_name::data);
        show();
    }
    else
    {
        ui->role_name->setText(name);
    }
}

void MainUI::on_star_but_clicked()
{
    ui->star_but->setEnabled(false);
    ui->end_but->setEnabled(true);
    QString msg = "一切准备就绪，开始修(mo)行(yu)！";
    AddMessage(msg);
//    emit SignalStartFishing();
    QJsonObject pub_obj;
    pub_obj.insert("type", uiCmd::StartFishing);
    pub_obj.insert("data", QJsonObject());
    emit SignalPubTopic(pub_obj);
}

void MainUI::on_end_but_clicked()
{
    ui->star_but->setEnabled(true);
    ui->end_but->setEnabled(false);
    QString msg = "修(mo)行(yu)暂时结束！";
    AddMessage(msg);
//    emit SignalStopFishing();
    QJsonObject pub_obj;
    pub_obj.insert("type", uiCmd::StopFishing);
    pub_obj.insert("data", QJsonObject());
    emit SignalPubTopic(pub_obj);
}

void MainUI::on_cultiva_up_but_clicked()
{
    RequestOutside(uiCmd::UpgradeLevel, module_name::role);
}

void MainUI::ShowLoginWidget()
{
    login_obj_->show();
}

void MainUI::ShowModifyNameWidget()
{
    modify_obj_->show();
}

void MainUI::CloseLoginWidget()
{
    login_obj_->close();
    emit SignalLogOut(QtInfoMsg, QMessageLogContext(), "关闭登录窗口");
}

void MainUI::CloseModifyNameWidget()
{
    modify_obj_->close();
    emit SignalLogOut(QtInfoMsg, QMessageLogContext(), "关闭命名窗口");
}

void MainUI::UpdateRoleUI(const QJsonObject& data) {
    QList<QString> keys = data.keys();
    for(const auto & key : keys)
    {
        QString new_data = data.value(key).toString();
        SlotUpdateUI((RoleUIEnum)key.toInt(), new_data);
    }
}

void MainUI::FistLogInDeal(int result) {
    switch (result)
    {
        case 0: // 非首次登录
        {
            RequestOutside(mainCmd::InitRemoteRoleInfo, module_name::data);
            show();
            break;
        }
        case 1: // 首次登录显示改名窗口
        {
            ShowModifyNameWidget();
            break;
        }
        default:
            break;
    }
}

void MainUI::AutomaticLogin(int result) {
    switch (result)
    {
        case 1:
            qDebug() << "自动登录，获取角色数据";
            RequestOutside(mainCmd::InitRemoteRoleInfo, module_name::data);
            show();
            break;
        case 0:
            // 进入登录、注册界面
            ShowLoginWidget();
            break;
        default:
            LOG_INFO(kUIManage, "自动登录检测错误结果");
    }
}

void MainUI::ModifyRoleNameDeal(int result) {
    modify_obj_->ModifyRoleNameDeal(result);
}

void MainUI::RoleNameIsOkDeal(int result) {
    modify_obj_->RoleNameIsOkDeal(result);
}

void MainUI::LoginVerificationDeal(int result) {
    login_obj_->LoginVerificationDeal(result);
}

void MainUI::AccountRegistrationDeal(int result) {
    login_obj_->AccountRegistrationDeal(result);
}

void MainUI::UpdateBackpackBar(QJsonObject data)
{
    for (auto it = data.begin(); it != data.end(); ++it) {
        QString key = it.key();
        QJsonArray list = it.value().toArray();

        if (key == "prop_list")
        {
            UpdateBackpackPropBar(list);
        }
        else if (key == "equip_list")
        {
            UpdateBackpackEquipBar(list);
        }
        else if (key == "material_list")
        {
            UpdateBackpackMaterialBar(list);
        }
        else if (key == "special_list")
        {
            UpdateBackpackSpecialBar(list);
        }
        else
        {
            LOG_INFO(kUIManage, "当前键值判断出错：" + key);
        }
    }
}

void MainUI::UpdateBackpackEquipBar(const QJsonArray& arr)
{

}

void MainUI::UpdateBackpackPropBar(const QJsonArray& arr)
{
    prop_map_ = QJsonObject();
    show_prop_info_ = QJsonObject();
    for (const QJsonValue &val : arr) {
        QJsonObject obj = val.toObject();
        if (obj.contains("prop_name")) {
            QString propValue = obj["prop_name"].toString();
            QListWidgetItem *item = new QListWidgetItem(propValue);
            ui->item_prop_list->addItem(item);
        }
        prop_map_.insert(obj.value("prop_name").toString(), obj.value("prop_index").toInt());
        show_prop_info_.insert(obj.value("prop_name").toString(), obj);
    }
}

void MainUI::UpdateBackpackMaterialBar(const QJsonArray& arr)
{

}

void MainUI::UpdateBackpackSpecialBar(const QJsonArray& arr)
{

}

void MainUI::on_item_preview_Widget_currentChanged(int index)
{
    switch (index)
    {
        case 0: // 装备
            break;
        case 1: // 道具
            ui->item_prop_list->clear();
            RequestOutside(uiCmd::UpdatePropShow, module_name::item);
            break;
        case 2: // 材料
            break;
        case 3: // 特殊
            break;
    }
}

void MainUI::RequestOutside(const QString& cmd, const QString& dest)
{
    emit SignalActionRequest(PublicFunc::PackageRequest(cmd,
                                                        QJsonObject(),
                                                        "",
                                                        dest,
                                                        module_name::ui));
}

void MainUI::on_sys_news_list_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(ui->sys_news_list);
    QAction clearAction("清屏", ui->sys_news_list);
    menu.addAction(&clearAction);

    QObject::connect(&clearAction, &QAction::triggered, [&]() {
        ui->sys_news_list->clear();
    });

    menu.exec(QCursor::pos());
}


void MainUI::on_item_prop_list_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *item = ui->item_prop_list->itemAt(pos);
    if(item)
    {
        QMenu menu(ui->item_prop_list);

        QAction useAction("使用", ui->item_prop_list);
        QAction sellAction("出售", ui->item_prop_list);

        menu.addAction(&useAction);
        menu.addAction(&sellAction);

        QObject::connect(&useAction, &QAction::triggered, [&]() {
            // 处理使用操作
            QString prop_name = item->text();
            AddMessage("使用道具：" + prop_name);
            QJsonObject data_obj;
            data_obj.insert("prop_index", prop_map_.value(prop_name).toInt());
            data_obj.insert("prop_name", prop_name);
            data_obj.insert("num", 1);
            emit SignalActionRequest(PublicFunc::PackageRequest(itemCmd::UseProps,
                                                                data_obj,
                                                                "",
                                                                module_name::item,
                                                                module_name::ui));
        });

        QObject::connect(&sellAction, &QAction::triggered, [&]() {
            // 处理出售操作
            QString prop_name = item->text();
            AddMessage("出售道具：" + prop_name);
        });
        menu.exec(ui->item_prop_list->mapToGlobal(pos));
    }

}

