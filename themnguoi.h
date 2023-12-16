#ifndef THEMNGUOI_H
#define THEMNGUOI_H

#include <QDialog>
#include <QtSql>
#include <QSqlQueryModel>

namespace Ui {
class themnguoi;
}

class themnguoi : public QDialog
{
    Q_OBJECT

public:
    explicit themnguoi(QWidget *parent = nullptr);
    ~themnguoi();

private slots:
    void on_pb_cancel_clicked();
    void on_pb_save_clicked();

private:
    Ui::themnguoi *ui;

    QString originalHoTen;
    QString originalUser;
    QString originalMk;
    QString originalSDT;
    QString originalEmail;
    QString originalDiachi;
};

#endif // THEMNGUOI_H
