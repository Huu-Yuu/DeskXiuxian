#include "modifyrolename.h"
#include "ui_modifyrolename.h"

ModifyRoleName::ModifyRoleName(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ModifyRoleName)
{
    ui->setupUi(this);

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

ModifyRoleName::~ModifyRoleName()
{
    delete ui;
}
