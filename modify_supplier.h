#ifndef MODIFY_SUPPLIER_H
#define MODIFY_SUPPLIER_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>

namespace Ui {
class modify_supplier;
}

class modify_supplier : public QDialog
{
    Q_OBJECT

public:
    explicit modify_supplier(QWidget *parent = nullptr);
    ~modify_supplier();

private slots:
    void on_tv_nha_cung_cap_activated(const QModelIndex &index);

    void on_pb_sua_nha_cung_cap_clicked();

    void on_pb_xoa_nha_cung_cap_clicked();

    void on_pb_thoat_clicked();

private:
    Ui::modify_supplier *ui;
};

#endif // MODIFY_SUPPLIER_H
