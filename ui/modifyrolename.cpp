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
    if(role_name_ok)
    {
        if(data_file_->ModifyRoleName(roleName_) == 1)
        {
            qDebug() << "修改成功！";
        }
        else
        {
            ui->tip_text->setText("修改失败，请检查网络连接");
        }
    }
}

void ModifyRoleName::on_check_btn_clicked()
{
    QString msg;
    roleName_ = ui->name_text->text();
    QRegularExpression regex("^[a-zA-Z0-9\\u4e00-\\u9fa5]{2,6}$");
    if (!regex.isValid()) {
        qDebug() << "正则表达式对象无效，处理错误情况";
    }
    QRegularExpressionMatch match = regex.match(roleName_);
    if (match.hasMatch() && match.captured(0) == roleName_)
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
