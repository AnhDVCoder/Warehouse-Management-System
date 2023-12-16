#include "nguoidung.h"
#include "ui_nguoidung.h"
#include <QInputDialog>
#include <QMessageBox>

profile::profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);

    connect(ui->pb_cancel, &QPushButton::clicked, this, &profile::on_pb_cancel_clicked);
    connect(ui->pb_sua, &QPushButton::clicked, this, &profile::on_pb_sua_clicked);
    connect(ui->pb_save_prf, &QPushButton::clicked, this, &profile::on_pb_save_clicked);
}

void profile::on_pb_sua_clicked()
{
    originalFullName = ui->le_fullname->text();
    originalEmail = ui->le_email->text();
    originalPhone = ui->le_phone->text();
    originalAddress = ui->le_address->text();

    ui->le_fullname->setReadOnly(false);
    ui->le_email->setReadOnly(false);
    ui->le_phone->setReadOnly(false);
    ui->le_address->setReadOnly(false);

    ui->pb_cancel->setVisible(true);
    ui->pb_save_prf->setVisible(true);
    ui->pb_sua->setVisible(false);
}

void profile::updateDataFromEditDialog(const QString &newFullName, const QString &newEmail, const QString &newPhone, const QString &newAddress)
{
    ui->le_fullname->setText(newFullName);
    ui->le_email->setText(newEmail);
    ui->le_phone->setText(newPhone);
    ui->le_address->setText(newAddress);
}

void profile::on_pb_cancel_clicked()
{
    ui->le_fullname->setReadOnly(true);
    ui->le_email->setReadOnly(true);
    ui->le_phone->setReadOnly(true);
    ui->le_address->setReadOnly(true);

    ui->pb_cancel->setVisible(false);
    ui->pb_save_prf->setVisible(false);
    ui->pb_sua->setVisible(true);

    ui->le_fullname->setText(originalFullName);
    ui->le_email->setText(originalEmail);
    ui->le_phone->setText(originalPhone);
    ui->le_address->setText(originalAddress);
    close();
}

void profile::dialog_warning() {
    QMessageBox wrn;
    wrn.warning(this, tr("Lỗi"), tr("1"));

}

void profile::on_pb_save_clicked()
{
    QString newFullName = ui->le_fullname->text();
    QString newEmail = ui->le_email->text();
    QString newPhone = ui->le_phone->text();
    QString newAddress = ui->le_address->text();

    // Kiểm tra nếu bất kỳ trường nào là rỗng
    if (newFullName.isEmpty() || newEmail.isEmpty() || newPhone.isEmpty() || newAddress.isEmpty()) {
        dialog_warning();
        return;
    }

    // Thực hiện lưu dữ liệu vào cơ sở dữ liệu hoặc các công việc lưu khác

    ui->le_fullname->setReadOnly(true);
    ui->le_email->setReadOnly(true);
    ui->le_phone->setReadOnly(true);
    ui->le_address->setReadOnly(true);

    ui->pb_cancel->setVisible(false);
    ui->pb_save_prf->setVisible(false);
    ui->pb_sua->setVisible(true);
}

profile::~profile()
{
    delete ui;
}
