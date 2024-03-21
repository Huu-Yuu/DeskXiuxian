#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QStyle>
#include <QDesktopWidget>
#include <QJsonObject>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "modules/filedata/data_service.h"

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
    void LoginVerificationDeal(int result);   ///< 登录校验处理  1-登录成功 0-账号或密码错误 -1-数据库连接失败
    void AccountRegistrationDeal(int result);   ///< 注册结果交互 1-注册成功 0-注册失败 -2-数据库连接失败 -1-账号已存在

signals:
    /**
     * @brief 登录成功信号
     */
    void SignalLoginSuccessful();

    //请求外部动作
    void SignalActionRequest(const QJsonObject& request_data);
    //本模块动作执行结果抛给上一级
    void SignalActionResponse(const QJsonObject& response_data);
    //状态变化抛给上一级
    void SignalPubTopic(const QJsonObject& pub_data);

private slots:

    void on_star_btn_clicked();

    void on_reg_btn_clicked();

    void on_username_text_textChanged(const QString& arg1);

    void on_password_text_textChanged(const QString& arg1);

    void on_email_text_textChanged(const QString& arg1);

private:
    Ui::LoginWindow* ui;
    bool user_name_ok = false;      // 检查输入格式是否正常
    bool pass_word_ok = false;
    bool email_ok = false;
    QString user_name_;
    QString pass_word_;
    QString eMail_;
};

#endif // LOGINWINDOW_H
