#ifndef SQL_H
#define SQL_H
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>

#endif // SQL_H

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
