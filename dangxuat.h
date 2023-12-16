// logoutconfirmation.h
#ifndef DANGXUAT_H
#define DANGXUAT_H

#include <QDialog>

namespace Ui {
class dangxuat;
}

class dangxuat : public QDialog
{
    Q_OBJECT

public:
    explicit dangxuat(QWidget *parent = nullptr);
    ~dangxuat();

private slots:
    void on_buttonBox_accepted();

private:
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // LOGOUTCONFIRMATION_H
