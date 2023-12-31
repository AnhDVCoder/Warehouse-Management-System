#include "export_product.h"
#include "ui_export_product.h"
#include <QMessageBox>

export_product::export_product(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::export_product)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");

    QStringList list_product_name, list_retail_name;
    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
    }
    else{
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT tenSP FROM san_pham");
        for (int i = 0; i < model->rowCount(); i++){
            list_product_name << model->record(i).value("tenSP").toString();
        }

        model->setQuery("SELECT tenDL FROM dai_ly");
        for (int i = 0; i < model->rowCount(); i++){
            list_retail_name << model->record(i).value("tenDL").toString();
        }
    }


    ui->cb_product->addItems(list_product_name);
    ui->cb_dai_ly->addItems(list_retail_name);
}

export_product::~export_product()
{
    delete ui;
}

void export_product::on_cb_product_currentIndexChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    int maSP, maPL, maNCC, so_luong_con;
    int san_pham = ui->cb_product->currentIndex();
    model->setQuery("SELECT maSP FROM san_pham");
    maSP = model->record(san_pham).value("maSP").toInt();
    ui->le_msp->setText(QString::number(maSP));

    model->setQuery("SELECT gia_xuat, maPL, maNCC, so_luong FROM san_pham WHERE maSP =" + QString::number(maSP));
    ui->le_export_price->setText(model->record(0).value("gia_xuat").toString());
    maPL = model->record(0).value("maPL").toInt();
    maNCC = model->record(0).value("maNCC").toInt();
    so_luong_con = model->record(0).value("so_luong").toInt();
    ui->le_so_luong_con->setText(QString::number(so_luong_con));

    model->setQuery("SELECT tenPL FROM phan_loai WHERE maPL =" + QString::number(maPL));
    ui->le_category->setText(model->record(0).value("tenPL").toString());

    model->setQuery("SELECT tenNCC FROM nha_cung_cap WHERE maNCC =" + QString::number(maNCC));
    ui->le_supplier->setText(model->record(0).value("tenNCC").toString());
}


void export_product::on_cb_dai_ly_currentIndexChanged(int index)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    int dai_ly = ui->cb_product->currentIndex();
    int maDL;

    model->setQuery("SELECT maDL FROM dai_ly");
    maDL = model->record(dai_ly).value("maDL").toInt();

    model->setQuery("SELECT tenDL, dia_chi, sdtDL, email FROM dai_ly WHERE maDL =" + QString::number(maDL));
    ui->le_maDL->setText(QString::number(maDL));
    ui->le_dia_chiDL->setText(model->record(0).value("dia_chi").toString());
    ui->le_sdtDL->setText(model->record(0).value("sdtDL").toString());


}


void export_product::on_pb_export_clicked()
{
    QDateTime date = QDateTime::currentDateTime();
    QString thoi_gian = date.toString("yyyy-MM-dd hh:mm:ss");

    QSqlQueryModel *model = new QSqlQueryModel;
    int maDL, maSP, so_luong_con, so_luong_xuat, gia_xuat, maND, maNCC;
    QString tenSP, tenDL, thongbao;

    maDL = ui->le_maDL->text().toInt();
    tenDL = ui->cb_dai_ly->currentText();
    maSP = ui->le_msp->text().toInt();
    tenSP = ui->cb_product->currentText();
    so_luong_con = ui->le_so_luong_con->text().toInt();
    so_luong_xuat = ui->sb_so_luong_xuat->text().toInt();
    gia_xuat = ui->le_export_price->text().toLongLong();
    maND = 2;

    model->setQuery("SELECT maNCC FROM san_pham WHERE maSP = " + QString::number(maSP));
    maNCC = model->record(0).value("tenNCC").toInt();

    model->setQuery("SELECT tenNCC FROM nha_cung_cap WHERE maNCC = " + QString::number(maNCC));
    // tenNCC = model->record(san_pham).value("tenNCC").toString();

    if(so_luong_xuat > so_luong_con){
        QMessageBox::warning(this, "Xuất kho", "Số lượng sản phẩm xuất đi vượt quá số lượng hiện có!");
    }
    else{
        model->setQuery("INSERT INTO thong_ke (ngayTK, so_luong_xuat, maSP, tenSP, maND) VALUES('" + thoi_gian + "', " + QString::number(so_luong_xuat) + ", " + QString::number(maSP) + ", '" + tenSP + "', '" + QString::number(maND) + "')");
        model->setQuery("INSERT INTO phieu_xuat (maND, maDL, maSP, tenDL, tenSP, so_luong_xuat, gia_xuat, thoi_gian) VALUES('" + QString::number(maND) + "', " + QString::number(maDL) + ", " + QString::number(maSP) + ", '" + tenDL + "', '" + tenSP + "', " + QString::number(so_luong_xuat) + ", " + QString::number(gia_xuat) + ", '" + thoi_gian + "')");
        model->setQuery("UPDATE san_pham SET so_luong = so_luong - " + QString::number(so_luong_xuat) + " WHERE maSP = " + QString::number(maSP));
        QMessageBox::information(this, "Xuất kho", "Xuất kho thành công!");
        ui->cb_product->setCurrentIndex(-1);
        ui->cb_dai_ly->setCurrentIndex(-1);
        ui->sb_so_luong_xuat->setValue(0);
    }
}


void export_product::on_pb_cancel_clicked()
{
    close();
}

