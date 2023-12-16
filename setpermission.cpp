#include "setpermission.h"
#include "ui_setpermission.h"

setpermission::setpermission(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setpermission)
{
    ui->setupUi(this);
}

setpermission::~setpermission()
{
    delete ui;
}
