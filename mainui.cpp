#include "mainui.h"
#include "ui_mainui.h"

MainUI::MainUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);
    // 初始化成员变量
    logger_obj_ = Logger::GetInstance();
    data_file_ = DataManage::GetInstance();
    process = new QProcess;

    // 初始化UI设置
    // 设置logo
    setWindowIcon(QIcon(":/res/logo.jpg"));

    // 设置窗口标题
    setWindowTitle("桌面修仙");

    // 固定窗口
    setFixedSize(width(),height());

    // 将窗口居中显示
    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size(),
                    qApp->desktop()->availableGeometry()
                    )
                );

    //外层widget布局
    ui->centralwidget->setLayout(ui->outerLayout);

    //主角选项卡布局
    ui->role_page->setLayout(ui->role_Layout);
    ui->bisic_Att_Box->setLayout(ui->bisic_Layout);
    ui->equipment_Box->setLayout(ui->equipment_Layout);

    QString msg = "当前游戏版本为：";
    QString game_vision = "v0.0.1 草稿版本";
    AddMessage(msg + game_vision);
}

MainUI::~MainUI()
{
    delete ui;
}

void MainUI::closeEvent(QCloseEvent *event)
{
    qDebug() << "检测到手动关闭游戏，强制结束进程";
    // 打印到日志
    emit SignalLogOut( QtFatalMsg, QMessageLogContext(), "检测到手动关闭游戏，强制结束进程");
    data_file_->SetGameLastPlayTime();
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

Ui::MainUI* MainUI::GetUI()
{
    return ui;
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
                         QString britches, QString shoe, QString jewelrt, QString mount)
{
    ui->equip_weapon->setText(weapon);
    ui->equip_magic->setText(magic);
    ui->equip_helmet->setText(helmet);
    ui->equip_clothing->setText(clothing);
    ui->equip_britches->setText(britches);
    ui->equip_shoe->setText(shoe);
    ui->equip_jewelry->setText(jewelrt);
    ui->equip_mount->setText(mount);
}

void MainUI::SlotUpdateUI(RoleUI part, QString new_data)
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

void MainUI::on_star_but_clicked()
{
    ui->star_but->setEnabled(false);
    ui->end_but->setEnabled(true);
    QString msg = "一切准备就绪，开始修(mo)行(yu)！";
    AddMessage(msg);
    emit SignalStartFishing();
}


void MainUI::on_end_but_clicked()
{
    ui->star_but->setEnabled(true);
    ui->end_but->setEnabled(false);
    QString msg = "修(mo)行(yu)暂时结束！";
    AddMessage(msg);
    emit SignalStopFishing();
}

void MainUI::on_cultiva_up_but_clicked()
{
    emit SignalUpgradeLevel();
}

