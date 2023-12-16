#ifndef QUAN_LI_DAI_LI_H
#define QUAN_LI_DAI_LI_H

#include <QDialog>
#include <QDialog>
#include <QListView>
#include <QtSql>
#include <QStringListModel>
namespace Ui {
class quan_li_dai_li;
}

class quan_li_dai_li : public QDialog
{
    Q_OBJECT

public:
    explicit quan_li_dai_li(QWidget *parent = nullptr);
    ~quan_li_dai_li();
private slots:
    void on_pb_timkiem_dl_clicked();
    void on_pb_xoa_dl_clicked();
    void on_pb_thoat_dl_clicked();
    void timKiemDaiLi(const QString &tuKhoa);
    void loadDaiLiListView();
    void on_listView_clicked(const QModelIndex &index);
    void on_pb_sua_dl_save();
    void on_pb_sua_dl_save_clicked();
private:
    Ui::quan_li_dai_li *ui;
    QStringListModel *model;
    QListView *listView;
    QString selectedDL; // Lưu trữ đại lí được chọn
    QString id; // maDL duoc chon
    QString maDl;
    QString tenDL; // tenND duoc chon
    QString dia_chidl; //
    QString sdtDl; //
    QString email;    // email duoc chon
    QString maDH;
};

#endif // QUAN_LI_DAI_LI_H
