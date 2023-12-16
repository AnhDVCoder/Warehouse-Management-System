#ifndef THEM_DAI_LY_H
#define THEM_DAI_LY_H

#include <QDialog>
#include <QtSql>
#include <QSqlQueryModel>

namespace Ui {
class them_dai_ly;
}

class them_dai_ly : public QDialog
{
    Q_OBJECT

public:
    explicit them_dai_ly(QWidget *parent = nullptr);
    ~them_dai_ly();

private slots:
    void on_pb_cancel_clicked();
    void on_pb_save_clicked();

private:
    Ui::them_dai_ly *ui;

    QString originalTen;
    QString originalDiachi;
    QString originalSDT;
    QString originalEmail;
};

#endif // THEMNGUOI_H
