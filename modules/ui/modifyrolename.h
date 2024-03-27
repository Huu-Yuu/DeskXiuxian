#ifndef MODIFYROLENAME_H
#define MODIFYROLENAME_H

#include <QDialog>
#include <QStyle>
#include <QDesktopWidget>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <regex>
#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include "modules/filedata/data_service.h"

namespace Ui
{
    class ModifyRoleName;
}

class ModifyRoleName : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyRoleName(QWidget* parent = nullptr);
    ~ModifyRoleName();
    void ModifyRoleNameDeal(int result);  ///< 重命名交互
    void RoleNameIsOkDeal(int result);     ///< 处理角色名是否重复结果

signals:
    /**
     * @brief 重命名成功 信号
     */
    void SignalRenameSuccessful(QString name);

    //请求外部动作
    void SignalActionRequest(const QJsonObject& request_data);
    //本模块动作执行结果抛给上一级
    void SignalActionResponse(const QJsonObject& response_data);
    //状态变化抛给上一级
    void SignalPubTopic(const QJsonObject& pub_data);

private slots:

    void on_star_btn_clicked();

    void on_check_btn_clicked();

private:
    Ui::ModifyRoleName* ui;
    QString role_name_;
    bool role_name_ok = false;      // 检查输入格式是否正常
};

#endif // MODIFYROLENAME_H
