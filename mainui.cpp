#include "mainui.h"
#include "ui_mainui.h"

MainUI::MainUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);
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

}

MainUI::~MainUI()
{
    delete ui;
}

