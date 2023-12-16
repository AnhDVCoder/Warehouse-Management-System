#include "add_category.h"
#include "ui_add_category.h"
#include <QMessageBox>
#include <QStringList>

add_category::add_category(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_category)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");
    QSqlQueryModel *model = new QSqlQueryModel;

    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
    }
    else{
        model->setQuery("SELECT maPL, tenPL FROM phan_loai WHERE maPL != 0");
        ui->tv_list_phan_loai->setModel(model);
    }


}

add_category::~add_category()
{
    delete ui;
}

void add_category::on_pb_save_clicked()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");

    QString tenPL = ui->le_category_name->text();

    if(!mydb.open()){
        QMessageBox::information(this, "Database", "Fail connect to DB!");
    }else{
        if(tenPL == ""){
            QMessageBox::warning(this, "Lỗi", "Chưa nhập tên phân loại!");
        }
        else{
            if(!mydb.open()){
                QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
            }
            else{
                QSqlQueryModel *model = new QSqlQueryModel;
                model->setQuery("INSERT INTO phan_loai (tenPL) VALUES('" + tenPL + "')");
                QMessageBox::information(this, "Thêm phân loại", "Thêm phân loại thành công!");
                model->setQuery("SELECT maPL, tenPL FROM phan_loai");
                ui->tv_list_phan_loai->setModel(model);
            }
        }
    }
}


void add_category::on_pb_cancel_clicked()
{
    close();
}


void add_category::on_tableView_activated(const QModelIndex &index){}


void add_category::on_tv_list_phan_loai_activated(const QModelIndex &index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString val = ui->tv_list_phan_loai->model()->data(index).toString();
    model->setQuery("SELECT maPL FROM phan_loai WHERE maPL = " + val);

    ui->le_category_nid->setText(model->record(0).value("maPL").toString());
}


void add_category::on_pb_xoa_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    int maPL = ui->le_category_nid->text().toInt();

    model->setQuery("DELETE FROM phan_loai WHERE maPL = " + QString::number(maPL));
    model->setQuery("UPDATE san_pham SET maPL = 0 WHERE maPL = " + QString::number(maPL));
    QMessageBox::information(this, "Phân loại", "Xóa phân loại thành công!");
    ui->le_category_name->setText("");
    ui->le_category_nid->setText("");
}

