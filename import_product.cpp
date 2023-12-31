#include "import_product.h"
#include "ui_import_product.h"
#include <QMessageBox>
#include <QStringList>
#include <QTableWidgetItem>

import_product::import_product(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::import_product)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");

    QStringList list_product_name, list_supplier_name, list_supplier_id;
    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
    }
    else{
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT tenSP FROM san_pham");
        for (int i = 0; i < model->rowCount(); i++){
            list_product_name << model->record(i).value("tenSP").toString();
        }
    }


    ui->cb_product->addItems(list_product_name);


}



import_product::~import_product()
{
    delete ui;
}

void import_product::on_pb_save_clicked()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");
    QSqlQueryModel *model = new QSqlQueryModel;

    int san_pham = ui->cb_product->currentIndex();
    long long so_luong = ui->sb_so_luong->text().toULongLong();
    bool flag1, flag2, flag3;
    QString thongbao, tenSP, tenNCC;
    int maND = 2;
    long long gia_nhap;

    QDateTime date = QDateTime::currentDateTime();
    QString thoi_gian = date.toString("yyyy-MM-dd hh:mm:ss");
    int maSP, maNCC;


    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
        flag1 = false;
    }
    else{
        flag1 = true;
    }

    if(flag1 == true){
        if(so_luong == NULL){
            thongbao += "- Chưa nhập số lượng!";
            flag2 = false;
        }
        else if(so_luong <= 0){
            thongbao += "- Số lượng nhập phải lớn hơn 0!";
            flag2 = false;
        }
        else{
            flag2 = true;
        }


        model->setQuery("SELECT maSP, tenSP, maNCC, gia_nhap FROM san_pham");
        maSP = model->record(san_pham).value("maSP").toInt();
        tenSP = model->record(san_pham).value("tenSP").toString();
        maNCC = model->record(san_pham).value("maNCC").toInt();
        gia_nhap = model->record(san_pham).value("gia_nhap").toLongLong();

        model->setQuery("SELECT tenNCC FROM nha_cung_cap WHERE maNCC = " + QString::number(maNCC));
        tenNCC = model->record(0).value("tenNCC").toString();



    }

    if(flag1 == true && flag2 == true){

        model->setQuery("INSERT INTO thong_ke (ngayTK, so_luong_nhap, maSP, tenSP, maND) VALUES('" + thoi_gian + "', " + QString::number(so_luong) + ", " + QString::number(maSP) + ", '" + tenSP + "', '" + QString::number(maND) + "')");
        model->setQuery("INSERT INTO phieu_nhap (maND, maNCC, maSP, tenNCC, tenSP, so_luong_nhap, gia_nhap, thoi_gian) VALUES('" + QString::number(maND) + "', " + QString::number(maNCC) + ", " + QString::number(maSP) + ", '" + tenNCC + "', '" + tenSP + "', " + QString::number(so_luong) + ", " + QString::number(gia_nhap) + ", '" + thoi_gian + "')");
        model->setQuery("UPDATE san_pham SET so_luong = so_luong + " + QString::number(so_luong) + " WHERE maSP = " + QString::number(maSP));
        QMessageBox::information(this, "Nhập kho", "Nhập kho thành công!");
    }
    else{
        QMessageBox::information(this, "Nhập kho", thongbao);
    }
}


void import_product::on_cb_ncc_currentIndexChanged(int index)
{

}


void import_product::on_cb_product_currentIndexChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    int maSP, maPL, maNCC;
    int san_pham = ui->cb_product->currentIndex();
    model->setQuery("SELECT maSP FROM san_pham");
    maSP = model->record(san_pham).value("maSP").toInt();

    model->setQuery("SELECT gia_nhap, maPL, maNCC FROM san_pham WHERE maSP =" + QString::number(maSP));
    ui->le_import_price->setText(model->record(0).value("gia_nhap").toString());
    maPL = model->record(0).value("maPL").toInt();
    maNCC = model->record(0).value("maNCC").toInt();

    model->setQuery("SELECT tenPL FROM phan_loai WHERE maPL =" + QString::number(maPL));
    ui->le_category->setText(model->record(0).value("tenPL").toString());

    model->setQuery("SELECT tenNCC FROM nha_cung_cap WHERE maNCC =" + QString::number(maNCC));
    ui->le_supplier->setText(model->record(0).value("tenNCC").toString());
}


void import_product::on_le_SoLuong_textChanged(const QString &arg1)
{

}


void import_product::on_sb_so_luong_textChanged(const QString &arg1)
{
    int maSP;
    double gia_nhap;
    long long tong_tien;
    int san_pham = ui->cb_product->currentIndex();
    int so_luong = ui->sb_so_luong->text().toInt();
    QSqlQueryModel *model = new QSqlQueryModel;



    model->setQuery("SELECT maSP FROM san_pham");
    maSP = model->record(san_pham).value("maSP").toInt();
    model->setQuery("SELECT gia_nhap FROM san_pham WHERE maSP =" + QString::number(maSP));
    gia_nhap = model->record(0).value("gia_nhap").toDouble();
    tong_tien = gia_nhap * so_luong;

    ui->le_total->setText(QString::number(tong_tien));
}


void import_product::on_pb_cancel_clicked()
{
    close();
}

