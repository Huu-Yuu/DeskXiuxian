#include "modifyrolename.h"
#include "ui_modifyrolename.h"

ModifyRoleName::ModifyRoleName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyRoleName)
{
    ui->setupUi(this);
}

ModifyRoleName::~ModifyRoleName()
{
    delete ui;
}
