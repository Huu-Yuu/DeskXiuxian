#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "modules/public/public_declare.h"

LoginWindow::LoginWindow(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
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

LoginWindow::~LoginWindow()
{
    delete ui;
}

QJsonObject LoginWindow::GetUserInputInfo()
{
    QString user_name = ui->username_text->text();
    QString pass_word = ui->password_text->text();
    QString e_mail = ui->email_text->text();
    QJsonObject user_obj;
    user_obj.insert("UserName", user_name);
    user_obj.insert("PassWord", pass_word);
    user_obj.insert("EMail", e_mail);
    return user_obj;
}

void LoginWindow::on_reg_btn_clicked()
{
    // 检查格式是否正常
    if(user_name_ok && pass_word_ok && email_ok)
    {
        QJsonObject data_obj;
        data_obj.insert("user_name", user_name_);
        data_obj.insert("pass_word", pass_word_);
        data_obj.insert("e_mail", eMail_);
        emit SignalActionRequest(PublicFunc::PackageRequest(dbCmd::AccountRegistration,
                                                            data_obj,
                                                            "",
                                                            module_name::data,
                                                            module_name::ui));
    }
    else
    {
        ui->tip_text->setText("注册失败，请重新填写以上三个信息");
    }
}

void LoginWindow::on_star_btn_clicked()
{
    // 检查格式是否正常
    if(user_name_ok && pass_word_ok)
    {
        QJsonObject data_obj;
        data_obj.insert("user_name", user_name_);
        data_obj.insert("pass_word", pass_word_);
        emit SignalActionRequest(PublicFunc::PackageRequest(dbCmd::LoginVerification,
                                                            data_obj,
                                                            "",
                                                            module_name::data,
                                                            module_name::ui));
    }
}

void LoginWindow::on_username_text_textChanged(const QString& arg1)
{
    user_name_ = arg1;
    QRegularExpression regex("^[A-Za-z0-9]{6,16}$"); // 正则表达式规则
    QRegularExpressionMatch match = regex.match(user_name_); // 进行匹配
    if (match.hasMatch() && match.capturedStart() == 0 && match.capturedEnd() == user_name_.length())
    {
        ui->username_text->setStyleSheet("");
        user_name_ok = true;
        qDebug() << "匹配完成，获取到输入的账号为：" + user_name_;
    }
    else
    {
        ui->username_text->setStyleSheet("QLineEdit { color: red; }");
        user_name_.clear();
        user_name_ok = false;
        qDebug() << "匹配失败";
    }
}


void LoginWindow::on_password_text_textChanged(const QString& arg1)
{
    pass_word_ = arg1;
    QRegularExpression regex("^[A-Za-z0-9]{6,16}$"); // 正则表达式规则
    QRegularExpressionMatch match = regex.match(pass_word_); // 进行匹配
    if (match.hasMatch() && match.capturedStart() == 0 && match.capturedEnd() == pass_word_.length())
    {
        ui->password_text->setStyleSheet("");
        pass_word_ok = true;
        qDebug() << "匹配完成，获取到输入的密码为：" + pass_word_;
    }
    else
    {
        ui->password_text->setStyleSheet("QLineEdit { color: red; }");
        pass_word_.clear();
        pass_word_ok = false;
        qDebug() << "匹配失败";
    }
}


void LoginWindow::on_email_text_textChanged(const QString& arg1)
{
    eMail_ = arg1;
    QRegularExpression regex("^[A-Za-z0-9_.]{3,18}@[A-Za-z0-9_-]+(\\.[A-Za-z0-9_-]+)*\\.[A-Za-z]{2,}$"); // 正则表达式规则
    QRegularExpressionMatch match = regex.match(eMail_); // 进行匹配

    if (match.hasMatch())
    {
        ui->email_text->setStyleSheet("");
        email_ok = true;
        qDebug() << "匹配成功，获取到输入的邮箱为：" << eMail_;
    }
    else
    {
        ui->email_text->setStyleSheet("QLineEdit { color: red; }");
        eMail_.clear();
        qDebug() << "匹配失败";
    }
}

void LoginWindow::LoginVerificationDeal(int result) {
    QString msg = "填入信息格式不正确，请修改后重试";
    switch (result)
    {
        case -1:
        {
            msg = "与服务器网络连接异常";
            break;
        }
        case 0:
        {
            msg = "账号或密码错误";
            break;
        }
        case 1:
        {
            // 登录成功
            msg = "登录成功";
            QJsonObject data_obj;
            data_obj.insert("user_name", user_name_);
            data_obj.insert("pass_word", pass_word_);
            data_obj.insert("e_mail", eMail_);
            emit SignalActionRequest(PublicFunc::PackageRequest(dbCmd::SetUserInfoToConfig,
                                                                data_obj,
                                                                "",
                                                                module_name::data,
                                                                module_name::ui));
            emit SignalLoginSuccessful();
            break;
        }
        default:
        {
            msg = "登录时出现未知错误";
            break;
        }
    }
    ui->tip_text->setText(msg);
}

void LoginWindow::AccountRegistrationDeal(int result) {
    QString msg = "填入信息格式不正确，请修改后重试";
    switch (result)
    {
        case -2:
        {
            msg = "与服务器网络连接异常";
            break;
        }
        case -1:
        {
            msg = "账号已存在";
            break;
        }
        case 0:
        {
            msg = "网络连接异常";
            break;
        }
        case 1:
        {
            msg = "注册成功，请登录";
            ui->reg_btn->setEnabled(false);
            break;
        }
        default:
            msg = "注册时出现未知错误";
            break;
    }
    ui->tip_text->setText(msg);
}

