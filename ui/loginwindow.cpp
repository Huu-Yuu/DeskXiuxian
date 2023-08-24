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


    // 写入正则限制
    QRegularExpression user_name_Regex("^[A-Za-z0-9]{6,16}$");
    QRegularExpressionValidator userNamelValidator(user_name_Regex);
    ui->username_text->setValidator(&userNamelValidator);

    QRegularExpression pass_word_Regex("^[A-Za-z0-9]{6,16}$");
    QRegularExpressionValidator passWordlValidator(pass_word_Regex);
    ui->password_text->setValidator(&passWordlValidator);

    QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b");
    QRegularExpressionValidator emailValidator(emailRegex);
    ui->email_text->setValidator(&emailValidator);
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
    user_obj.insert("UserName",user_name);
    user_obj.insert("PassWord",pass_word);
    user_obj.insert("EMail",e_mail);
    return user_obj;
}

void LoginWindow::on_email_text_textChanged(const QString &arg1)
{
    if (ui->email_text->hasAcceptableInput()) {
        ui->email_text->setStyleSheet("");
        email_ok = true;
        CheckLoginIsPossible();
    } else {
        ui->email_text->setStyleSheet("QLineEdit { background-color: red; }");
        email_ok = false;
    }
    qDebug() << "获取到输入的邮箱为：" << arg1;
}


void LoginWindow::on_username_text_textChanged(const QString &arg1)
{
    if (ui->username_text->hasAcceptableInput()) {
        ui->username_text->setStyleSheet("");
        user_name_ok = true;
        CheckLoginIsPossible();
    } else {
        ui->username_text->setStyleSheet("QLineEdit { background-color: red; }");
        user_name_ok = false;
    }
    qDebug() << "获取到输入的账号为：" << arg1;
}


void LoginWindow::on_password_text_textChanged(const QString &arg1)
{
    if (ui->password_text->hasAcceptableInput()) {
        ui->password_text->setStyleSheet("");
        pass_word_ok = true;
        CheckLoginIsPossible();
    } else {
        ui->password_text->setStyleSheet("QLineEdit { background-color: red; }");
        pass_word_ok = false;
    }
    qDebug() << "获取到输入的密码为：" << arg1;
}

void LoginWindow::CheckLoginIsPossible()
{
    if(user_name_ok && pass_word_ok && email_ok)
    {
        ui->star_btn->setEnabled(true);
    }
    else
    {
        ui->star_btn->setEnabled(false);
    }
}

void LoginWindow::on_close_btn_clicked()
{
    close();
}

void LoginWindow::on_star_btn_clicked()
{
    // 登录验证
    QString userName = ui->username_text->text();
    QString passWord = ui->password_text->text();
    bool result = data_file_->LoginVerification(userName, passWord);
    if(result)
    {
        // 登录成功
        QMessageBox::information(nullptr, "提示", "登录成功");
        close();
    }
    // 注册
    result = data_file_->AccountRegistration(userName, passWord);
    if(result)
    {
        // 注册成功
        QMessageBox::information(nullptr, "提示", "注册成功");
    }
    else
    {
        // 注册成功
        QMessageBox::information(nullptr, "提示", "注册失败，用户名已存在或网络异常");
    }
}

