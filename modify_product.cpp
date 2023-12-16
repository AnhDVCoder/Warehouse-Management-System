#include "modify_product.h"
#include "ui_modify_product.h"
#include <QMessageBox>
#include <QStringList>

modify_product::modify_product(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::modify_product)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");

    QStringList list_category, list_supplier_name;
    if(!mydb.open()){
        QMessageBox::information(this, "Database", "Fail connect to Database!");
    }
    else{
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT maPL, tenPL FROM phan_loai");
        // list_category << "";
        for (int i = 0; i < model->rowCount(); i++){
            list_category << model->record(i).value("tenPL").toString();
        }

        model->setQuery("SELECT maNCC, tenNCC FROM nha_cung_cap");
        // list_supplier_name << "";
        for (int i = 0; i < model->rowCount(); i++){
            list_supplier_name << model->record(i).value("TenNCC").toString();
        }

        // model->setQuery("SELECT MaSP FROM san_pham ORDER BY MaSP DESC LIMIT 1");


        ui->cb_phan_loai->addItems(list_category);
        ui->cb_nha_cung_cap->addItems(list_supplier_name);
         ui->cb_phan_loai->setCurrentIndex(0);
        ui->cb_nha_cung_cap->setCurrentIndex(0);

        model->setQuery("SELECT maSP, tenSP, gia_nhap, gia_xuat, so_luong FROM san_pham");
        ui->tv_list_san_pham->setModel(model);


    }




}

modify_product::~modify_product()
{
    delete ui;
}

void modify_product::on_tv_list_san_pham_activated(const QModelIndex &index)
{
    QString value = ui->tv_list_san_pham->model()->data(index).toString();
    int maPL, maNCC, temp;
    QString tenPL, check;
    QStringList listPL;


    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM san_pham WHERE maSP =" + value);
    check = model->record(0).value("maSP").toString();
    if(check == ""){
        ui->le_msp->setText("");
        ui->le_tensp->setText("");
        ui->cb_phan_loai->setCurrentIndex(0);
        ui->sb_gia_nhap->setValue(NULL);
        ui->sb_gia_xuat->setValue(NULL);
        ui->cb_nha_cung_cap->setCurrentIndex(0);
    }
    else{
        ui->le_msp->setText(model->record(0).value("maSP").toString());
        ui->le_tensp->setText(model->record(0).value("tenSP").toString());
        maPL = model->record(0).value("maPL").toInt();
        ui->sb_gia_nhap->setValue(model->record(0).value("gia_nhap").toLongLong());
        ui->sb_gia_xuat->setValue(model->record(0).value("gia_xuat").toLongLong());
        maNCC = model->record(0).value("maNCC").toInt();
    }






    model->setQuery("SELECT maPL FROM phan_loai");
    for (int i = 0; i < model->rowCount(); i++){
        temp = model->record(i).value("maPL").toInt();
        if(maPL == temp){
            ui->cb_phan_loai->setCurrentIndex(i);
        }
    }

    model->setQuery("SELECT maNCC FROM nha_cung_cap");
    for (int i = 0; i < model->rowCount(); i++){
        temp = model->record(i).value("maNCC").toInt();
        if(maNCC == temp){
            ui->cb_nha_cung_cap->setCurrentIndex(i);

        }
    }
}


void modify_product::on_pb_sua_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    int maSP = ui->le_msp->text().toInt();
    QString tensp = ui->le_tensp->text();
    int phan_loai = ui->cb_phan_loai->currentIndex();
    double gia_nhap = ui->sb_gia_nhap->text().toDouble();
    double gia_xuat = ui->sb_gia_xuat->text().toDouble();
    int nha_cung_cap = ui->cb_nha_cung_cap->currentIndex();





    bool flag1, flag2, flag3, flag4;
    QString thongbao;
    int maNCC, maPL;



    if(maSP != NULL){
        if(tensp == ""){
            thongbao += "- Chua nhap ten san pham!\n";
            flag1 = false;
        }
        else{
            flag1 = true;
        }

        if(phan_loai == NULL){
            thongbao += "- Chua chon phan loai!\n";
            maPL = 0;
        }
        else{
            model->setQuery("SELECT maPL FROM phan_loai");
            maPL = model->record(phan_loai).value("maPL").toInt();
        }

        if(gia_nhap < 0){
            thongbao += "- Gia nhap khong duoc nho hon 0!\n";
            flag2 = false;
        }
        else{
            flag2 = true;
        }

        if(gia_xuat < 0){
            thongbao += "- Gia xuat khong duoc nho hon 0!\n";
            flag3 = false;
        }
        else{
            flag3 = true;
        }

        if(nha_cung_cap == NULL){
            thongbao += "- Chua chon nha cung cap!\n";
            flag4 = false;
        }
        else{
            model->setQuery("SELECT maNCC FROM nha_cung_cap");
            maNCC = model->record(nha_cung_cap).value("maNCC").toInt();
            flag4 = true;
        }



        // if(!mydb.open()){
        //     QMessageBox::information(this, "Database", "Fail connect to Database!");
        // }
        // else{
        if(flag1 == true && flag2 == true && flag3 == true && flag4 == true){

            model->setQuery("UPDATE san_pham SET tenSP = '" + tensp + "', maPL = " + QString::number(maPL) + ", gia_nhap = " + QString::number(gia_nhap) + ", gia_xuat = " + QString::number(gia_xuat) + ", maNCC = " + QString::number(maNCC) + " WHERE maSP = " + QString::number(maSP));
            QMessageBox::information(this, "San pham", "Sua thanh cong!");
            // thongbao = tensp + "\n" + QString::number(maPL) + "\n" + gia_nhap + "\n" + gia_xuat + "\n" + QString::number(maNCC);
            // QMessageBox::information(this, "Them san pham", thongbao);
            model->setQuery("SELECT maSP, tenSP, gia_nhap, gia_xuat, so_luong FROM san_pham");
            ui->tv_list_san_pham->setModel(model);
        }
        else{
            QMessageBox::information(this, "Error", thongbao);
        }

    }
    else{
        QMessageBox::information(this, "Error", "Ban chua chon san pham!");
    }
}


void modify_product::on_pb_xoa_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    int maSP = ui->le_msp->text().toInt();
    if(maSP != NULL){
        model->setQuery("DELETE FROM san_pham WHERE maSP = " + QString::number(maSP));
        QMessageBox::information(this, "Error", "Xoa thanh cong!");
        model->setQuery("SELECT maSP, tenSP, gia_nhap, gia_xuat, so_luong FROM san_pham");
        ui->tv_list_san_pham->setModel(model);
        ui->le_msp->setText("");
        ui->le_tensp->setText("");
        ui->cb_phan_loai->setCurrentIndex(0);
        ui->sb_gia_nhap->setValue(NULL);
        ui->sb_gia_xuat->setValue(NULL);
        ui->cb_nha_cung_cap->setCurrentIndex(0);
    }
    else{
        QMessageBox::information(this, "Error", "Ban chua chon san pham can xoa!");
    }
}


void modify_product::on_pb_huy_clicked()
{
    close();
}

