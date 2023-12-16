#ifndef MODIFY_PRODUCT_H
#define MODIFY_PRODUCT_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>
#include <QComboBox>

namespace Ui {
class modify_product;
}

class modify_product : public QDialog
{
    Q_OBJECT

public:
    explicit modify_product(QWidget *parent = nullptr);
    ~modify_product();

private slots:
    void on_tv_list_san_pham_activated(const QModelIndex &index);

    void on_pb_sua_clicked();

    void on_pb_xoa_clicked();

    void on_pb_huy_clicked();

private:
    Ui::modify_product *ui;
};

#endif // MODIFY_PRODUCT_H
