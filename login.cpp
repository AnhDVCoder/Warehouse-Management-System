#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "sql.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{

    ui->setupUi(this);

    if(!ConnOpen()){
        QMessageBox::information(this, "Database", "Fail connect to Database!");
    }





}

login::~login()
{
    delete ui;
}

void login::on_pb_login_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    QString username = ui->le_username->text();
    QString password = ui->le_password->text();

    ConnOpen();
    if(!mydb.open()){
        QMessageBox::warning(this, "CSDL", "Không kết nối được tới cơ sở dữ liệu!");
    }
    if(username.trimmed() == "" || password.trimmed() == ""){
        QMessageBox::warning(this, "Thông báo", "Vui lòng nhập đầy đủ thông tin!");
    }
    else{
        model->setQuery("SELECT username, password FROM nguoi_dung WHERE username = '" + username + "' AND password = '" + password + "'");
        QString check_username = model->record(0).value("username").toString();
        QString check_password = model->record(0).value("password").toString();
        if(username == check_username && password == check_password){
            QMessageBox::information(this, "Đăng nhập", "Đăng nhập thành công!");
            hide();
            overview = new class overview(this);
            overview->show();
        }
        else{
            QMessageBox::warning(this, "Đăng nhập", "Đăng nhập không thành công, vui lòng kiểm tra lại tài khoản hoặc mật khẩu!");
        }
    }





}

