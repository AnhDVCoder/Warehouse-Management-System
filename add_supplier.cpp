#include "add_supplier.h"
#include "ui_add_supplier.h"
#include <QMessageBox>
#include <QStringList>
#include <QRegularExpression>

add_supplier::add_supplier(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_supplier)
{
    ui->setupUi(this);


    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");

    QSqlQueryModel *model = new QSqlQueryModel;

    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
    }
    else{
        model->setQuery("SELECT * FROM nha_cung_cap WHERE maNCC != 0");
        ui->tv_nha_cung_cap->setModel(model);
    }

}

add_supplier::~add_supplier()
{
    delete ui;
}

void add_supplier::on_pushButton_2_clicked()
{
    close();
}


void add_supplier::on_pushButton_clicked()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");

    QSqlQueryModel *model = new QSqlQueryModel;

    bool flag1, flag2, flag3, flag4, flag5;

    QString tenNCC = ui->le_tenNCC->text();
    QString diaChi = ui->le_dia_chi->text();
    QString sdtNCC = ui->le_sdtNCC->text();
    QString emailNCC = ui->le_emailNCC->text();

    QString thongbao;

    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
        flag1 = false;
    }
    else{
        flag1 = true;
    }

    if(flag1 == true){
        if(tenNCC.trimmed() == ""){
            thongbao += "- Chưa nhập tên nhà cung cấp!\n";
            flag2 = false;
        }
        else{
            model->setQuery("SELECT tenNCC FROM nha_cung_cap WHERE tenNCC = '" + tenNCC.trimmed() + "'");
            QString check = model->record(0).value("tenNCC").toString();
            if(check != ""){

                thongbao += "- Tên nhà cung cấp đã tồn tại!\n";
                flag2 = false;
            }
            else{
                flag2 = true;
            }

        }

        if(diaChi.trimmed() == ""){
            thongbao += "- Chưa nhập địa chỉ!\n";
            flag3 = false;
        }
        else{
            flag3 = true;
        }


        QRegularExpression re("^\\d+$");
        QRegularExpressionMatch match;

        bool hasMatch;



        if(sdtNCC.trimmed() == ""){
            thongbao += "- Chưa điền số điện thoại!\n";
            flag4 = false;
        }
        else{
            match = re.match(sdtNCC);
            if(!match.hasMatch()){
                thongbao += "- Số điện thoại không hợp lệ!\n";
                flag4 = false;
            }
            else{
                model->setQuery("SELECT sdtNCC FROM nha_cung_cap WHERE sdtNCC = '" + sdtNCC.trimmed() + "'");
                QString check = model->record(0).value("sdtNCC").toString();
                if(check != ""){

                    thongbao += "- Số điện thoại đã tồn tại!\n";
                    flag4 = false;
                }
                else{
                    flag4 = true;
                }
            }

        }

        if(emailNCC.trimmed() == ""){
            thongbao += "- Chưa nhập email nhà cung cấp!\n";
            flag5 = false;
        }
        else{
            model->setQuery("SELECT email FROM nha_cung_cap WHERE email = '" + emailNCC.trimmed() + "'");
            QString check = model->record(0).value("email").toString();
            if(check != ""){

                thongbao += "- Email này đã tồn tại!\n";
                flag5 = false;
            }
            else{
                flag5 = true;
            }
        }

        if(flag2 == true && flag3 == true && flag4 == true && flag5 == true){

            model->setQuery("INSERT INTO nha_cung_cap (tenNCC, dia_chi, sdtNCC, email) VALUES('" + tenNCC + "', '" + diaChi + "', '" + sdtNCC + "', '" + emailNCC + "')");
            QMessageBox::information(this, "Nhà cung cấp", "Thêm nhà cung cấp thành công!");
            model->setQuery("SELECT * FROM nha_cung_cap");
            ui->tv_nha_cung_cap->setModel(model);
        }
        else{
            QMessageBox::warning(this, "Nhà cung cấp", thongbao);
        }

    }
    else{
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
    }

}


void add_supplier::on_tv_list_nha_cung_cap_activated(const QModelIndex &index){}

