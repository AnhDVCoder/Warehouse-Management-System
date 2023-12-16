#include "report.h"
#include "ui_report.h"
#include <QMessageBox>

report::report(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::report)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");
    QSqlQueryModel *model = new QSqlQueryModel;

    if(!mydb.open()){
        QMessageBox::warning(this, "Thông báo", "Không kết nối được tới cơ sở dữ liệu!");
    }
    else{
        model->setQuery("SELECT ngayTK, tenSP, so_luong_nhap, so_luong_xuat, maND FROM thong_ke ORDER BY ngayTK DESC");
        ui->tv_infomation->setModel(model);
    }
}

report::~report()
{
    delete ui;
}

void report::on_pb_import_status_clicked()
{

}


void report::on_comboBox_currentIndexChanged(int index)
{

}


void report::on_cb_statistic_currentIndexChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;

    QString order_by;

    int order_type = ui->le_order_by->text().toInt();
    if(order_type == 0){
        order_by = "ORDER BY thoi_gian DESC";
    }else if(order_type == 1){
        order_by = "ORDER BY thoi_gian ASC";
    }



    int statistic;
    statistic = ui->cb_statistic->currentIndex();
    if(statistic == 0){
        model->setQuery("SELECT thoi_gian, tenSP, tenNCC, so_luong_nhap, gia_nhap, maND FROM phieu_nhap " + order_by);
        ui->le_statistic->setText(QString::number(0));
    }else if(statistic == 1){
        model->setQuery("SELECT thoi_gian, tenSP, tenDL, so_luong_xuat, gia_xuat, maND FROM phieu_xuat " + order_by);
        ui->le_statistic->setText(QString::number(1));
    }else if(statistic == 2){
        model->setQuery("SELECT maSP, tenSP, so_luong FROM san_pham");
        ui->le_statistic->setText(QString::number(2));
    }
    ui->tv_infomation->setModel(model);


}


void report::on_cb_order_by_currentIndexChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;

    // QString order_by = "ORDER BY thoi_gian DESC";

    int order, statistic;
    QString order_by;
    order = ui->cb_order_by->currentIndex();
    statistic = ui->cb_statistic->currentIndex();

    if(order == 0){
        ui->le_order_by->setText(QString::number(0));
        if(statistic == 2){
            order_by = "ORDER BY maSP DESC";
        }
        else{
            order_by = "ORDER BY thoi_gian DESC";
        }

    }else if(order == 1){
        ui->le_order_by->setText(QString::number(1));
        if(statistic == 2){
            order_by = "ORDER BY maSP ASC";
        }
        else{
            order_by = "ORDER BY maSP ASC";
        }
    }

    if(statistic == 0){
        model->setQuery("SELECT thoi_gian, tenSP, tenNCC, so_luong_nhap, gia_nhap, maND FROM phieu_nhap " + order_by);
        ui->le_statistic->setText(QString::number(0));
    }else if(statistic == 1){
        model->setQuery("SELECT thoi_gian, tenSP, tenDL, so_luong_xuat, gia_xuat, maND FROM phieu_xuat " + order_by);
        ui->le_statistic->setText(QString::number(1));
    }else if(statistic == 2){
        model->setQuery("SELECT maSP, tenSP, so_luong FROM san_pham " + order_by);
        ui->le_statistic->setText(QString::number(2));
    }
    ui->tv_infomation->setModel(model);
}


void report::on_pb_out_clicked()
{
    this->hide();
}

