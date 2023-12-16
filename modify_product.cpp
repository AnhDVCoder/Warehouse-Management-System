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
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
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
            thongbao += "- Tên sản phẩm không được để trống!\n";
            flag1 = false;
        }
        else{
            flag1 = true;
        }

        if(phan_loai == NULL){
            thongbao += "- Chưa chọn phân loại!\n";
            maPL = 0;
        }
        else{
            model->setQuery("SELECT maPL FROM phan_loai");
            maPL = model->record(phan_loai).value("maPL").toInt();
        }

        if(gia_nhap < 0){
            thongbao += "- Giá nhập không được nhỏ hơn 0!\n";
            flag2 = false;
        }
        else{
            flag2 = true;
        }

        if(gia_xuat < 0){
            thongbao += "- Giá xuất không được nhỏ hơn 0!\n";
            flag3 = false;
        }
        else{
            flag3 = true;
        }

        if(nha_cung_cap == NULL){
            thongbao += "- Chưa chọn nhà cung cấp!\n";
            flag4 = false;
        }
        else{
            model->setQuery("SELECT maNCC FROM nha_cung_cap");
            maNCC = model->record(nha_cung_cap).value("maNCC").toInt();
            flag4 = true;
        }

        if(flag1 == true && flag2 == true && flag3 == true && flag4 == true){

            model->setQuery("UPDATE san_pham SET tenSP = '" + tensp + "', maPL = " + QString::number(maPL) + ", gia_nhap = " + QString::number(gia_nhap) + ", gia_xuat = " + QString::number(gia_xuat) + ", maNCC = " + QString::number(maNCC) + " WHERE maSP = " + QString::number(maSP));
            QMessageBox::information(this, "Sản phẩm", "Cập nhật sản phẩm thành công!");
            model->setQuery("SELECT maSP, tenSP, gia_nhap, gia_xuat, so_luong FROM san_pham");
            ui->tv_list_san_pham->setModel(model);
        }
        else{
            QMessageBox::warning(this, "Lỗi", thongbao);
        }

    }
    else{
        QMessageBox::warning(this, "Lỗi", "Bạn chưa chọn sản phẩm cần sửa!");
    }
}


void modify_product::on_pb_xoa_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    int maSP = ui->le_msp->text().toInt();
    if(maSP != NULL){
        model->setQuery("DELETE FROM san_pham WHERE maSP = " + QString::number(maSP));
        QMessageBox::information(this, "Sản phẩm", "Xóa sản phẩm thành công!");
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
        QMessageBox::information(this, "Lỗi", "Bạn chưa chọn sản phẩm cần xóa!");
    }
}


void modify_product::on_pb_huy_clicked()
{
    close();
}

