#include "modifyrolename.h"
#include "ui_modifyrolename.h"

ModifyRoleName::ModifyRoleName(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ModifyRoleName)
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

ModifyRoleName::~ModifyRoleName()
{
    delete ui;
}

void ModifyRoleName::on_star_btn_clicked()
{
    on_check_btn_clicked();
    QString msg;
    if(role_name_ok)
    {
        int result = data_file_->ModifyRoleName(roleName_);
        switch (result)
        {
            case 0:
            {
                msg = "修改失败，请重试";
                qDebug() << msg;
                break;
            }
            case 1:
            {
                msg = "修改成功";
                qDebug() << msg;
                emit SignalRenameSuccessful();
                break;
            }
            default:
            {
                msg = "修改失败，请检查网络连接";
                qDebug() << msg;
                break;
            }
        }

    }
    ui->tip_text->setText(msg);
}

void ModifyRoleName::on_check_btn_clicked()
{
    QString msg;
    roleName_ = ui->name_text->text();
    QRegExp regExp("^[a-zA-Z0-9\\u4e00-\\u9fa5]{2,6}$");
    if (regExp.exactMatch(roleName_))
    {
        // 字符串完全匹配，符合要求
        if(data_file_->CheckRoleNameIsOk(roleName_))
        {
            msg = "恭喜，昵称可用";
            role_name_ok = true;
        }
        else
        {
            msg = "昵称已存在，请重命名";
            role_name_ok = false;
        }
    }
    else
    {
        msg = "昵称格式不正确，请修改";
        role_name_ok = false;
    }
    ui->star_btn->setEnabled(role_name_ok);
    ui->tip_text->setText(msg);
}
