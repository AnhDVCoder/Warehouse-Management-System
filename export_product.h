#ifndef EXPORT_PRODUCT_H
#define EXPORT_PRODUCT_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>

namespace Ui {
class export_product;
}

class export_product : public QDialog
{
    Q_OBJECT

public:
    explicit export_product(QWidget *parent = nullptr);
    ~export_product();

private slots:
    void on_cb_product_currentIndexChanged(int index);

    void on_cb_dai_ly_currentIndexChanged(int index);

    void on_pb_export_clicked();

private:
    Ui::export_product *ui;
};

#endif // EXPORT_PRODUCT_H
