#include "them_dai_ly.h"
#include "ui_them_dai_ly.h"
#include <QMessageBox>

them_dai_ly::them_dai_ly(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::them_dai_ly)
{
    ui->setupUi(this);

    connect(ui->pb_huy_dl, &QPushButton::clicked, this, &them_dai_ly::on_pb_cancel_clicked);
    connect(ui->pb_luu_dl, &QPushButton::clicked, this, &them_dai_ly::on_pb_save_clicked);
}


void them_dai_ly::on_pb_cancel_clicked()
{
    ui->le_Ten_dl->setReadOnly(true);
    ui->le_diachi_dl->setReadOnly(true);
    ui->le_sdt_dl->setReadOnly(true);
    ui->le_email_dl->setReadOnly(true);

    ui->le_Ten_dl->setText(originalTen);
    ui->le_diachi_dl->setText(originalDiachi);
    ui->le_sdt_dl->setText(originalSDT);
    ui->le_email_dl->setText(originalEmail);

    close();
}

void them_dai_ly::on_pb_save_clicked()
{
    // QString newMaHD = ui->le_maHD_dl->text();
    QString newHotenDL = ui->le_Ten_dl->text();
    QString newSDTDL = ui->le_diachi_dl->text();
    QString newEmailDL = ui->le_sdt_dl->text();
    QString newDiaChiDl = ui->le_email_dl->text();

    // Kiểm tra nếu bất kỳ trường nào là rỗng
    if (newHotenDL.isEmpty()  || newSDTDL.isEmpty() || newEmailDL.isEmpty() || newDiaChiDl.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng điền đầy đủ thông tin.");
    } else {
        // Thực hiện lưu dữ liệu vào cơ sở dữ liệu
        QSqlQuery query;
        query.prepare("INSERT INTO dai_ly (tenDL, dia_chi, sdtDL, email) "
                      "VALUES (:hotenDL, :diachiDL, :sdtDL, :emailDL)");
        // query.bindValue(":maHD", newMaHD);
        query.bindValue(":hotenDL", newHotenDL);
        query.bindValue(":sdtDL", newSDTDL);
        query.bindValue(":emailDL", newEmailDL);
        query.bindValue(":diachiDL", newDiaChiDl);

        if (query.exec()){
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


them_dai_ly::~them_dai_ly()
{
    delete ui;
}
