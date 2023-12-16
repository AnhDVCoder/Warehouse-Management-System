#ifndef QUAN_LI_NGUOI_DUNG_H
#define QUAN_LI_NGUOI_DUNG_H

#include <QDialog>
#include <QListView>
#include <QtSql>
#include <QStringListModel>

namespace Ui {
class xoa_nguoi_dung;
}

class xoa_nguoi_dung : public QDialog
{
    Q_OBJECT

public:
    explicit xoa_nguoi_dung(QWidget *parent = nullptr);
    ~xoa_nguoi_dung();

private slots:
    void on_pb_timkiem_nd_clicked();
    void on_pb_xoa_nd_clicked();
    void on_pb_thoat_nd_clicked();
    void timKiemNguoiDung(const QString &tuKhoa);
    void loadNguoiDungListView();
    void on_listView_clicked(const QModelIndex &index);
    void on_pb_sua_nd_save();
    void on_pb_sua_nd_save_clicked();

private:
    Ui::xoa_nguoi_dung *ui;
    QStringListModel *model;
    QListView *listView;
    QString selectedUser; // Lưu trữ người dùng được chọn
    QString id; // maND duoc chon
    QString maND;
    QString tenND; // tenND duoc chon
    QString username; // username duoc chon
    QString password; // password duoc chon
    QString sdtND;  // sdtND duoc chon
    QString email;    // email duoc chon
    QString dia_chi;  // dia chi duoc chon
};

#endif // QUAN_LI_NGUOI_DUNG_H
