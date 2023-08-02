#include "mainui.h"
#include "ui_mainui.h"

MainUI::MainUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);
    //将主选项卡填充到窗口中
    setCentralWidget(ui->tabWidget);

    //主角选项卡布局
    ui->role_page->setLayout(ui->role_Layout);
    ui->bisic_Att_Box->setLayout(ui->bisic_Layout);
    ui->equipment_Box->setLayout(ui->equipment_Layout);

}

MainUI::~MainUI()
{
    delete ui;
}

