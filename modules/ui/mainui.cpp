#include "mainui.h"
#include "ui_mainui.h"
#include "modules/public/public_declare.h"

MainUI::MainUI(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);
    // 初始化成员变量
    logger_obj_ = Logger::getInstance();
    data_file_ = DataService::getInstance();
    role_item_ = ItemService::getInstance();
    login_obj_ = new LoginWindow;
    modify_obj_ = new ModifyRoleName;
    process = new QProcess;

    connect(login_obj_, &LoginWindow::SignalLoginSuccessful, this, &MainUI::SlotLoginSuccessful);
    connect(modify_obj_, &ModifyRoleName::SignalRenameSuccessful, this, &MainUI::SlotRenameSuccessful);

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

    QString date_time_str = QString("%1 %2").arg(__DATE__).arg(__TIME__);
    if (date_time_str.contains("  "))
    {
        date_time_str.replace("  ", " ");
    }
    QDateTime compile_data_time = QLocale(QLocale::English)
            .toDateTime(date_time_str, "MMM d yyyy hh:mm:ss");
    QString compile_time = compile_data_time.toString("yyyy.MM.dd hh:mm:ss");
    QString msg = QString("当前游戏版本为：%1/n发布日期：%2").arg(GAME_VISION).arg(compile_time);
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
    data_file_->SetGameConfigInfo();
    // 杀死所有进程
    QString command = "taskkill /F /IM DeskXiuxian.exe";
    process->start(command);
    process->waitForFinished();

    QMainWindow::closeEvent(event);
}

void MainUI::AddMessage(QString msg)
{
    QString time_stamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm:ss");

    QString display_text = time_stamp + "：" + msg;

    ui->listWidget->addItem(display_text);
    // 滚动到底部
    ui->listWidget->scrollToBottom();
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
    int result = data_file_->CheckUserLogginIsFist();
    switch (result)
    {
        case 0: // 非首次登录
        {
//            emit SignalInitRoleData();
            emit SignalActionRequest(PublicFunc::PackageRequest(mainCmd::InitRemoteRoleInfo,
                                                                QJsonObject(),
                                                                "",
                                                                module_name::data,
                                                                module_name::ui));
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

void MainUI::SlotRenameSuccessful()
{
    CloseModifyNameWidget();
    // 初始化远程数据库
//    emit SignalInitRoleData();
    emit SignalActionRequest(PublicFunc::PackageRequest(mainCmd::InitRemoteRoleInfo,
                                                        QJsonObject(),
                                                        "",
                                                        module_name::data,
                                                        module_name::ui));
    show();
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
//    emit SignalUpgradeLevel();
    emit SignalActionRequest(PublicFunc::PackageRequest(uiCmd::UpgradeLevel,
                                                        QJsonObject(),
                                                        "",
                                                        module_name::role,
                                                        module_name::ui));
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
