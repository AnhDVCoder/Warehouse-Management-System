#ifndef SUA_NGUOI_DUNG_H
#define SUA_NGUOI_DUNG_H

#include <QDialog>

namespace Ui {
class Sua_nguoi_dung;
}

class Sua_nguoi_dung : public QDialog
{
    Q_OBJECT

public:
    explicit Sua_nguoi_dung(QWidget *parent = nullptr);
    ~Sua_nguoi_dung();

private:
    Ui::Sua_nguoi_dung *ui;
};

#endif // SUA_NGUOI_DUNG_H
