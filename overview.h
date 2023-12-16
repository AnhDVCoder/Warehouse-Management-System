#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QMainWindow>
#include "add_category.h"
#include "add_product.h"
#include "add_supplier.h"
#include "import_product.h"
#include "modify_product.h"
#include "modify_supplier.h"
#include "export_product.h"
// #include "login.h"
//hoang
#include "nguoidung.h"
#include "themnguoi.h"
#include "quan_li_nguoi_dung.h"
#include "phanquyen.h"
#include "quan_li_dai_li.h"
#include"them_dai_ly.h"
class login;

namespace Ui {
class overview;
}

class overview : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void ConnClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool ConnOpen()
    {
        mydb = QSqlDatabase::addDatabase("QSQLITE");

        mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");
        if(!mydb.open()){
            qDebug() << "Khong ket noi duoc toi Database";
            return false;
        }else
        {
            qDebug() << "Ket noi thanh cong toi Database";
            return true;
        }
    }
public:
    explicit overview(QWidget *parent = nullptr);
    ~overview();

private slots:
    void on_action_profile_triggered();

    void on_actionSetPermission_triggered();

    void on_action_add_product_triggered();

    void on_action_add_category_triggered();

    void on_action_import_goods_triggered();

    void on_action_supplier_triggered();

    void on_action_modify_product_triggered();

    void on_action_add_supplier_triggered();

    void on_action_modify_supplier_triggered();

    void on_action_export_goods_triggered();

    void on_action_themnguoi_triggered();

    void on_action_xoa_nguoi_triggered();

    void on_action_themdaili_triggered();

    void on_action_quan_li_dai_ly_triggered();

    void on_action_logout_triggered();

private:
    Ui::overview *ui;
    add_product *add_product;
    add_category *add_category;
    import_product *import_product;
    add_supplier *add_supplier;
    modify_product *modify_product;
    modify_supplier *modify_supplier;
    export_product *export_product;

    themnguoi *themnguoi;
    xoa_nguoi_dung *xoa_nguoi_dung;
    login *loginWindow;
    quan_li_dai_li* quan_li_dai_li;
    them_dai_ly*them_dai_ly;
};

#endif // OVERVIEW_H
