// profile.h
#ifndef NGUOIDUNG_H
#define NGUOIDUNG_H

#include <QDialog>

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_pb_cancel_clicked();
    void on_pb_sua_clicked();
    void on_pb_save_clicked();
    void dialog_warning();

private:
    Ui::profile *ui;

    QString originalFullName;
    QString originalEmail;
    QString originalPhone;
    QString originalAddress;

    void updateDataFromEditDialog(const QString &newFullName, const QString &newEmail, const QString &newPhone, const QString &newAddress);
};

#endif // NGUOIDUNG_H
