#ifndef IMPORT_PRODUCT_H
#define IMPORT_PRODUCT_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>
// #include "sql.h"

namespace Ui {
class import_product;
}

class import_product : public QDialog
{
    Q_OBJECT

public:
    explicit import_product(QWidget *parent = nullptr);
    ~import_product();

private slots:
    void on_pb_save_clicked();

    void on_cb_ncc_currentIndexChanged(int index);

    void on_cb_product_currentIndexChanged(int index);

    void on_le_SoLuong_textChanged(const QString &arg1);

    void on_sb_so_luong_textChanged(const QString &arg1);

    void on_pb_cancel_clicked();

private:
    Ui::import_product *ui;
};

#endif // IMPORT_PRODUCT_H
