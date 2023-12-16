#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <QListView>
#include <QtSql>
#include <QStringListModel>

namespace Ui {
class report;
}

class report : public QDialog
{
    Q_OBJECT

public:
    explicit report(QWidget *parent = nullptr);
    ~report();

private slots:
    void on_pb_import_status_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_cb_statistic_currentIndexChanged(int index);

    void on_cb_order_by_currentIndexChanged(int index);

    void on_pb_out_clicked();

private:
    Ui::report *ui;
};

#endif // REPORT_H
