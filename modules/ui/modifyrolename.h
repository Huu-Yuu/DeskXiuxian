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

signals:
    /**
     * @brief 重命名成功 信号
     */
    void SignalRenameSuccessful();

private slots:

    void on_star_btn_clicked();

    void on_check_btn_clicked();

private:
    Ui::ModifyRoleName* ui;
    QString roleName_;
    bool role_name_ok = false;      // 检查输入格式是否正常
    DataService* data_file_;         // 文件管理对象
};

#endif // MODIFYROLENAME_H
