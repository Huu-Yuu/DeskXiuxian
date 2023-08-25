#ifndef MODIFYROLENAME_H
#define MODIFYROLENAME_H

#include <QDialog>
#include <QStyle>
#include <QDesktopWidget>

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

private:
    Ui::ModifyRoleName* ui;
};

#endif // MODIFYROLENAME_H
