#include "modify_supplier.h"
#include "ui_modify_supplier.h"
#include <QMessageBox>
#include <QStringList>
#include <QRegularExpression>

modify_supplier::modify_supplier(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::modify_supplier)
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

modify_supplier::~modify_supplier()
{
    delete ui;
}

void modify_supplier::on_tv_nha_cung_cap_activated(const QModelIndex &index)
{
    QString value = ui->tv_nha_cung_cap->model()->data(index).toString();
    QString check;

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM nha_cung_cap WHERE maNCC =" + value);
    check = model->record(0).value("maNCC").toString();
    if(check == ""){
        ui->le_maNCC->setText("");
        ui->le_tenNCC->setText("");
        ui->le_dia_chi->setText("");
        ui->le_sdtNCC->setText("");
        ui->le_emailNCC->setText("");
    }
    else{
        ui->le_maNCC->setText(model->record(0).value("maNCC").toString());
        ui->le_tenNCC->setText(model->record(0).value("tenNCC").toString());
        ui->le_dia_chi->setText(model->record(0).value("dia_chi").toString());
        ui->le_sdtNCC->setText(model->record(0).value("sdtNCC").toString());
        ui->le_emailNCC->setText(model->record(0).value("email").toString());
    }
}


void modify_supplier::on_pb_sua_nha_cung_cap_clicked()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");

    QSqlQueryModel *model = new QSqlQueryModel;

    bool flag1, flag2, flag3, flag4, flag5;

    int maNCC = ui->le_maNCC->text().toInt();
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

    if(maNCC != NULL){
        if(tenNCC.trimmed() == ""){
            thongbao += "- Chưa nhập tên nhà cung cấp!\n";
            flag2 = false;
        }
        else{
            model->setQuery("SELECT tenNCC FROM nha_cung_cap WHERE tenNCC = '" + tenNCC.trimmed() + "' AND maNCC != " + QString::number(maNCC));
            QString check = model->record(0).value("tenNCC").toString();
            if(check != ""){

                thongbao += "- Số điện thoại đã tồn tại!\n";
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
            thongbao += "- Chưa nhập số điện thoại!\n";
            flag4 = false;
        }
        else{
            match = re.match(sdtNCC);
            if(!match.hasMatch()){
                thongbao += "- Số điện thoại không hợp lệ!\n";
                flag4 = false;
            }
            else{
                model->setQuery("SELECT sdtNCC FROM nha_cung_cap WHERE sdtNCC = '" + sdtNCC.trimmed() + "' AND maNCC != " + QString::number(maNCC));
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
            thongbao += "- Chưa nhập email!\n";
            flag5 = false;
        }
        else{
            model->setQuery("SELECT email FROM nha_cung_cap WHERE email = '" + emailNCC.trimmed() + "' AND maNCC != " + QString::number(maNCC));
            QString check = model->record(0).value("email").toString();
            if(check != ""){

                thongbao += "- Email đã tồn tại!\n";
                flag5 = false;
            }
            else{
                flag5 = true;
            }
        }

        if(flag2 == true && flag3 == true && flag4 == true && flag5 == true){


            model->setQuery("UPDATE nha_cung_cap SET tenNCC = '" + tenNCC + "', dia_chi = '" + diaChi + "', sdtNCC = '" + sdtNCC + "', email = '" + emailNCC + "' WHERE maNCC = " + QString::number(maNCC));
            QMessageBox::information(this, "Nhà cung cấp", "Sửa thông tin nhà cung cấp thành công!");
            model->setQuery("SELECT * FROM nha_cung_cap WHERE maNCC != 0");
            ui->tv_nha_cung_cap->setModel(model);
        }
        else{
            QMessageBox::warning(this, "Nhà cung cấp", thongbao);
        }

    }
    else{
        QMessageBox::warning(this, "Nhà cung cấp", "Bạn chưa chọn nhà cung cấp!");
    }
}


void modify_supplier::on_pb_xoa_nha_cung_cap_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    int maNCC = ui->le_maNCC->text().toInt();
    if(maNCC != NULL){
        model->setQuery("DELETE FROM nha_cung_cap WHERE maNCC = " + QString::number(maNCC));
        model->setQuery("UPDATE san_pham SET maNCC = 0 WHERE maNCC = " + QString::number(maNCC));
        QMessageBox::information(this, "Nhà cung cấp", "Xóa nhà cung cấp thành công!");
        model->setQuery("SELECT * FROM nha_cung_cap WHERE maNCC != 0");
        ui->tv_nha_cung_cap->setModel(model);
        ui->le_maNCC->setText("");
        ui->le_tenNCC->setText("");
        ui->le_dia_chi->setText("");
        ui->le_sdtNCC->setText("");
        ui->le_emailNCC->setText("");
    }
    else{
        QMessageBox::warning(this, "Nhà cung cấp", "Bạn chưa chọn nhà cung cấp!");
    }
}


void modify_supplier::on_pb_thoat_clicked()
{
    close();
}

