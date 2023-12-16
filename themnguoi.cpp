#include "themnguoi.h"
#include "ui_themnguoi.h"
#include <QMessageBox>

themnguoi::themnguoi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::themnguoi)
{
    ui->setupUi(this);

    connect(ui->pb_huy_tn_23, &QPushButton::clicked, this, &themnguoi::on_pb_cancel_clicked);
    connect(ui->pb_luu_tn_23, &QPushButton::clicked, this, &themnguoi::on_pb_save_clicked);
}


void themnguoi::on_pb_cancel_clicked()
{
    ui->le_hoten_tn->setReadOnly(true);
    ui->le_user_tn->setReadOnly(true);
    ui->le_mk_tn->setReadOnly(true);
    ui->le_sdt_tn->setReadOnly(true);
    ui->le_email_tn->setReadOnly(true);
    ui->le_diachi_tn->setReadOnly(true);

    ui->le_hoten_tn->setText(originalHoTen);
    ui->le_user_tn->setText(originalUser);
    ui->le_mk_tn->setText(originalMk);
    ui->le_sdt_tn->setText(originalSDT);
    ui->le_email_tn->setText(originalEmail);
    ui->le_diachi_tn->setText(originalDiachi);
    close();
}

void themnguoi::on_pb_save_clicked()
{
    QString newHoten1 = ui->le_hoten_tn->text();
    QString newUser1 = ui->le_user_tn->text();
    QString newMK1 = ui->le_mk_tn->text();
    QString newMKL1 = ui->le_mkl_tn->text(); // Assuming le_mkl is the QLineEdit for confirming the password
    QString newSDT1 = ui->le_sdt_tn->text();
    QString newEmail1 = ui->le_email_tn->text();
    QString newDiaChi1 = ui->le_diachi_tn->text();

    // Kiểm tra nếu bất kỳ trường nào là rỗng
    if (newHoten1.isEmpty() || newUser1.isEmpty() || newMK1.isEmpty() || newSDT1.isEmpty() || newEmail1.isEmpty() || newDiaChi1.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng điền đầy đủ thông tin.");
    } else if (newMK1 != newMKL1) {
        QMessageBox::warning(this, "Lỗi", "Mật khẩu và xác nhận mật khẩu không khớp.");
    } else {
        // Thực hiện lưu dữ liệu vào cơ sở dữ liệu
        QSqlQuery query;
        query.prepare("INSERT INTO nguoi_dung (tenND, username, password, sdtND, email, dia_chi) "
                      "VALUES (:hoten, :username, :matkhau, :sdt, :email, :diachi)");
        query.bindValue(":hoten", newHoten1);
        query.bindValue(":username", newUser1);
        query.bindValue(":matkhau", newMK1);
        query.bindValue(":sdt", newSDT1);
        query.bindValue(":email", newEmail1);
        query.bindValue(":diachi", newDiaChi1);

        if (query.exec()) {
            // Hiển thị thông báo thành công
            QMessageBox::information(this, "Thông báo", "Thêm người thành công!");

            // Đóng cửa sổ dialog
            accept();
        } else {
            // Hiển thị thông báo lỗi
            QMessageBox::critical(this, "Lỗi", "Không thể thêm người. Lỗi: " + query.lastError().text());
        }
    }
}


themnguoi::~themnguoi()
{
    delete ui;
}
