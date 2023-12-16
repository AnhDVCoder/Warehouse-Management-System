#ifndef SETPERMISSION_H
#define SETPERMISSION_H

#include <QDialog>

namespace Ui {
class setpermission;
}

class setpermission : public QDialog
{
    Q_OBJECT

public:
    explicit setpermission(QWidget *parent = nullptr);
    ~setpermission();

private:
    Ui::setpermission *ui;
};

#endif // SETPERMISSION_H
