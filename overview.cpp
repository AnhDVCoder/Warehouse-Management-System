#include "overview.h"
#include "add_category.h"
#include "add_product.h"
#include "import_product.h"
#include "add_supplier.h"
#include "modify_supplier.h"
#include "export_product.h"
#include "ui_overview.h"
#include "report.h"
#include <QMessageBox>
//Hoang
#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "nguoidung.h"
#include "themnguoi.h"
#include "phanquyen.h"
#include "dangxuat.h"
#include "ui_themnguoi.h"
#include "ui_quan_li_nguoi_dung.h"
#include "them_dai_ly.h"
#include "ui_quan_li_dai_li.h"

overview::overview(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::overview)
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
        ui->tv_statistic->setModel(model);
    }





}

overview::~overview()
{
    delete ui;
}

void overview::on_action_profile_triggered()
{
    nguoidung = new profile(this);
    nguoidung->show();

}


void overview::on_actionSetPermission_triggered()
{
    phanquyen = new class setpermission();
    phanquyen->show();

}


void overview::on_action_add_product_triggered()
{
    add_product = new class add_product(this);
    add_product->show();




}


void overview::on_action_add_category_triggered()
{
    add_category = new class add_category(this);
    add_category->show();
}


void overview::on_action_import_goods_triggered()
{
    import_product = new class import_product(this);
    import_product->show();
}


void overview::on_action_supplier_triggered()
{

}


void overview::on_action_modify_product_triggered()
{
    modify_product = new class modify_product(this);
    modify_product->show();
}


void overview::on_action_add_supplier_triggered()
{
    add_supplier = new class add_supplier(this);
    add_supplier->show();
}


void overview::on_action_modify_supplier_triggered()
{
    modify_supplier = new class modify_supplier(this);
    modify_supplier->show();
}


void overview::on_action_export_goods_triggered()
{
    export_product = new class export_product(this);
    export_product->show();
}


void overview::on_action_themnguoi_triggered()
{
    themnguoi = new class themnguoi(this);
    themnguoi->show();
}

void overview::on_action_xoa_nguoi_triggered()
{
    xoa_nguoi_dung = new class xoa_nguoi_dung(this);
    xoa_nguoi_dung->exec();
}

void overview::on_action_quan_li_dai_ly_triggered()
{
    quan_li_dai_li = new class quan_li_dai_li(this);
    quan_li_dai_li->exec();
}
void overview::on_action_themdaili_triggered()
{
    them_dai_ly = new class them_dai_ly(this);
    them_dai_ly->exec();
}
void overview::on_action_logout_triggered()
{
    // Add code to handle logout here
    // For example, you can show a login window
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận", "Bạn có chắc muốn đăng xuất?",
                                  QMessageBox::Yes|QMessageBox::No);

    // Nếu người dùng ấn Yes, đăng xuất và đóng cửa sổ chính
    if (reply == QMessageBox::Yes) {

        this->close();
        loginWindow = new class login(this);
        //loginWindow.exec();
        loginWindow->show();
    }

}


void overview::on_action_statistic_triggered()
{
    report = new class report();
             report->show();
}


void overview::on_action_transfer_goods_triggered()
{
    QMessageBox::information(this, "Thông báo", "Tính năng đang phát triển, sẽ cập nhật trong những phiên bản sau!");
}

