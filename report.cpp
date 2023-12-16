#include "report.h"
#include "ui_report.h"

report::report(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::report)
{
    ui->setupUi(this);
}

report::~report()
{
    delete ui;
}
