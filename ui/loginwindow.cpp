#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    data_file_->GetInstance();

    // 设置logo
    setWindowIcon(QIcon(":/res/logo.jpg"));

    // 将窗口居中显示
    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size(),
                    qApp->desktop()->availableGeometry()
                    )
                );
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
