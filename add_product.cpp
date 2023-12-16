#include "add_product.h"
#include "ui_add_product.h"
#include <QMessageBox>
#include <QStringList>

add_product::add_product(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_product)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");
    QSqlQueryModel *model = new QSqlQueryModel;

    QStringList list_category, list_supplier_name;
    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
    }
    else{
        model->setQuery("SELECT maPL, tenPL FROM phan_loai");
        for (int i = 0; i < model->rowCount(); i++){
            list_category << model->record(i).value("tenPL").toString();
        }

        model->setQuery("SELECT maNCC, tenNCC FROM nha_cung_cap");
        for (int i = 0; i < model->rowCount(); i++){
            list_supplier_name << model->record(i).value("TenNCC").toString();
        }

        model->setQuery("SELECT maSP, tenSP, gia_nhap, gia_xuat, so_luong FROM san_pham");
        ui->tv_list_san_pham->setModel(model);
        ui->cb_danhmuc->addItems(list_category);
        ui->cb_nha_cung_cap->addItems(list_supplier_name);

    }
}


add_product::~add_product()
{
    delete ui;
}

void add_product::on_pb_save_clicked()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");

    QSqlQueryModel *model = new QSqlQueryModel;

    QString tensp = ui->le_tensp->text();
    int danh_muc = ui->cb_danhmuc->currentIndex();
    double gia_nhap = ui->sb_gia_nhap->text().toDouble();
    double gia_xuat = ui->sb_gia_xuat->text().toDouble();
    int nha_cung_cap = ui->cb_nha_cung_cap->currentIndex();

    bool flag1, flag2, flag3, flag4;
    QString thongbao;
    int maNCC, maPL;

    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
    }else{
        if(tensp == ""){
            thongbao += "- Chưa nhập tên sản phẩm!\n";
            flag1 = false;
        }
        else{
            flag1 = true;
        }

        if(danh_muc == NULL){
            thongbao += "- Chưa chọn phân loại!\n";
            maPL = 0;
        }
        else{
            model->setQuery("SELECT maPL FROM phan_loai");
            maPL = model->record(danh_muc).value("maPL").toInt();
        }

        if(gia_nhap == NULL){
            thongbao += "- Chưa điền giá nhập!\n";
            flag2 = false;
        }
        else{
            flag2 = true;
        }

        if(gia_xuat == NULL){
            thongbao += "- Chưa điền giá xuất!\n";
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
            QSqlQueryModel *model = new QSqlQueryModel;
            model->setQuery("INSERT INTO san_pham (tenSP, maPL, gia_nhap, gia_xuat, maNCC) VALUES('" + tensp + "', " + QString::number(maPL) + ", " + QString::number(gia_nhap) + ", " + QString::number(gia_xuat) + ", " + QString::number(maNCC) + ")");
            QMessageBox::information(this, "Sản phẩm", "Thêm sản phẩm thành công!");
            model->setQuery("SELECT maSP, tenSP, gia_nhap, gia_xuat, maPL, maNCC FROM san_pham");
            ui->tv_list_san_pham->setModel(model);
        }
        else{
            QMessageBox::warning(this, "Lỗi", thongbao);
        }

    }
}


void add_product::on_pb_cancel_clicked()
{
    close();
}


void add_product::on_tv_list_san_pham_activated(const QModelIndex &index)
{
    QString val = ui->tv_list_san_pham->model()->data(index).toString();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT maNCC FROM nha_cung_cap");
}


void add_product::on_cb_danhmuc_activated(int index){}
void add_product::on_tv_list_san_pham_clicked(const QModelIndex &index){}

