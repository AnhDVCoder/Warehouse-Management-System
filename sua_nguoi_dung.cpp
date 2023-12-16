#include "sua_nguoi_dung.h"
#include "ui_sua_nguoi_dung.h"

Sua_nguoi_dung::Sua_nguoi_dung(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Sua_nguoi_dung)
{
    ui->setupUi(this);
}

Sua_nguoi_dung::~Sua_nguoi_dung()
{
    delete ui;
}
