#ifndef ADD_SUPPLIER_H
#define ADD_SUPPLIER_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>

namespace Ui {
class add_supplier;
}

class add_supplier : public QDialog
{
    Q_OBJECT

public:
    explicit add_supplier(QWidget *parent = nullptr);
    ~add_supplier();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tv_list_nha_cung_cap_activated(const QModelIndex &index);

private:
    Ui::add_supplier *ui;
};

#endif // ADD_SUPPLIER_H
