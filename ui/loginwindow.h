#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QStyle>
#include <QDesktopWidget>
#include "filedata/datamanage.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

    DataManage* data_file_;         // 文件管理对象
    QString userName_;
    QString passWord_;
    QString eMail_;
    QString uuid;
};

#endif // LOGINWINDOW_H
