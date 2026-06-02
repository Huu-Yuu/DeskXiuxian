#include "modifyrolename.h"
#include "ui_modifyrolename.h"
#include "modules/public/public_func.h"
#include "modules/public/public_declare.h"
#include <QGuiApplication>
#include <QScreen>
#include <QJsonObject>

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
            QGuiApplication::primaryScreen()->availableGeometry()
        )
    );
    this->setMaximumWidth(this->width());
    this->setMaximumHeight(this->height());
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
        QJsonObject data_obj;
        data_obj.insert("name", role_name_);
        emit SignalActionRequest(PublicFunc::PackageRequest(roleCmd::ModifyRoleName,
                                                            data_obj,
                                                            "",
                                                            module_name::data,
                                                            module_name::ui));
    }
}

void ModifyRoleName::on_check_btn_clicked()
{
    QString msg;
    role_name_ = ui->name_text->text();

    if (role_name_.isEmpty())
    {
        msg = "昵称不能为空，请修改";
        role_name_ok = false;
        ui->star_btn->setEnabled(role_name_ok);
        ui->tip_text->setText(msg);
        return;
    }

    // 检查长度（1-6个字符）
    if (role_name_.length() > 6)
    {
        msg = "昵称长度不能超过6个字符，请修改";
        role_name_ok = false;
        ui->star_btn->setEnabled(role_name_ok);
        ui->tip_text->setText(msg);
        return;
    }

    // 逐个字符检查：只允许汉字、数字、字母
    bool isValid = true;
    for (QChar ch : role_name_)
    {
        // 不允许任何标点符号、特殊符号、符号、空格
        if (ch.isPunct() || ch.isSymbol() || ch.isMark() || ch.isSpace())
        {
            isValid = false;
            break;
        }
        // 只允许数字、字母（包括汉字，汉字也是 Letter）
        if (!(ch.isDigit() || ch.isLetter()))
        {
            isValid = false;
            break;
        }
    }

    if (isValid)
    {
        // 字符串完全匹配，符合要求，查询数据库是否名称是否可用
        QJsonObject data_obj;
        data_obj.insert("name", role_name_);
        emit SignalActionRequest(PublicFunc::PackageRequest(dbCmd::CheckRoleNameIsOk,
                                                            data_obj,
                                                            "",
                                                            module_name::data,
                                                            module_name::ui));
    }
    else
    {
        msg = "昵称格式不正确，请修改";
        role_name_ok = false;
        ui->star_btn->setEnabled(role_name_ok);
        ui->tip_text->setText(msg);
    }
}

void ModifyRoleName::ModifyRoleNameDeal(int result) {
    QString msg;
    switch (result)
    {
        case 0:
        {
            msg = "修改失败，请重试";
            break;
        }
        case 1:
        {
            msg = "修改成功";
            QJsonObject data_obj;
            data_obj.insert("name", role_name_);
            emit SignalActionRequest(PublicFunc::PackageRequest(roleCmd::ModifyRoleName,
                                                                data_obj,
                                                                "",
                                                                module_name::role,
                                                                module_name::ui));
            emit SignalRenameSuccessful(role_name_);
            ShowMsgToUi("重命名角色：" + role_name_);
            break;
        }
        default:
        {
            msg = "修改失败，请检查网络连接";
            break;
        }
    }
    ui->tip_text->setText(msg);
}

void ModifyRoleName::RoleNameIsOkDeal(int result) {
    QString msg;
    if(result == 1)
    {
        msg = "恭喜，昵称可用";
        role_name_ok = true;
    }
    else
    {
        msg = "昵称已存在，请重命名";
        role_name_ok = false;
    }
    ui->star_btn->setEnabled(role_name_ok);
    ui->tip_text->setText(msg);
}

void ModifyRoleName::ShowMsgToUi(const QString &msg) {
    QJsonObject data_obj;
    data_obj.insert("msg", msg);
    emit SignalActionRequest(PublicFunc::PackageRequest(uiCmd::ShowMsgToUI,
                                                        data_obj,
                                                        "",
                                                        module_name::ui,
                                                        module_name::ui));
}
