// setpermission.h
#ifndef PHANQUYEN_H
#define PHANQUYEN_H

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

private slots:
    void on_pb_search_clicked();
    void on_pb_save_clicked();
    void on_pb_cancel_clicked(); // Thêm hàm xử lý sự kiện cho nút hủy
    void on_listView_itemSelectionChanged(); // Thêm hàm xử lý sự kiện khi chọn mục trong list

private:
    Ui::setpermission *ui;

    // Hàm xử lý chức năng tìm kiếm
    void performSearch(const QString &searchText);

    // Hàm xử lý chức năng lưu
    void performSave();

    // Hàm xử lý chức năng hủy
    void performCancel();

    // Hàm xử lý khi chọn mục trong list
    void updatePermissionList();

    // TODO: Khai báo các hàm xử lý khác nếu cần
};

#endif // PHANQUYEN_H
