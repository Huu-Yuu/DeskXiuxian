#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QStyle>
#include <QDesktopWidget>
#include <QJsonObject>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "modules/filedata/datamanage.h"

namespace Ui
{
    class LoginWindow;
}

/**
 * @brief 登录界面
 */
class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

    QJsonObject GetUserInputInfo();

signals:
    /**
     * @brief 登录成功信号
     */
    void SignalLoginSuccessful();

private slots:

    void on_star_btn_clicked();

    void on_reg_btn_clicked();

    void on_username_text_textChanged(const QString& arg1);

    void on_password_text_textChanged(const QString& arg1);

    void on_email_text_textChanged(const QString& arg1);

private:
    Ui::LoginWindow* ui;

    DataManage* data_file_;         // 文件管理对象
    bool user_name_ok = false;      // 检查输入格式是否正常
    bool pass_word_ok = false;
    bool email_ok = false;
    QString userName_;
    QString passWord_;
    QString eMail_;
};

#endif // LOGINWINDOW_H
