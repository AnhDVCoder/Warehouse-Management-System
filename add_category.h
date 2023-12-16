#ifndef ADD_CATEGORY_H
#define ADD_CATEGORY_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQueryModel>

namespace Ui {
class add_category;
}

class add_category : public QDialog
{
    Q_OBJECT

public:
    explicit add_category(QWidget *parent = nullptr);
    ~add_category();

private slots:
    void on_pb_save_clicked();

    void on_pb_cancel_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_tv_list_phan_loai_activated(const QModelIndex &index);

    void on_pb_xoa_clicked();

private:
    Ui::add_category *ui;
};

#endif // ADD_CATEGORY_H
