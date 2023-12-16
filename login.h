#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "overview.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>

// #include "user.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

// public:
//     QSqlDatabase mydb;
//     void ConnClose(){
//         mydb.close();
//         mydb.removeDatabase(QSqlDatabase::defaultConnection);
//     }
//     bool ConnOpen()
//     {
//         mydb = QSqlDatabase::addDatabase("QSQLITE");

//         mydb.setDatabaseName(QCoreApplication::applicationDirPath() + "/warehouse-sqlite.db");
//         if(!mydb.open()){
//             qDebug() << "Khong ket noi duoc toi Database";
//             return false;
//         }else
//         {
//             qDebug() << "Ket noi thanh cong toi Database";
//             return true;
//         }
//     }
public:
    explicit login(QWidget *parent = nullptr);
    ~login();
// signals:
//     void accept(const user &user);
// private slots:
//     void on_buttonBox_accepted();

private slots:
    void on_pb_login_clicked();

private:
    Ui::login *ui;
    overview *overview;

};

#endif // LOGIN_H
