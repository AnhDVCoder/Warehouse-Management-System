// setpermission.cpp
#include "phanquyen.h"
#include "ui_phanquyen.h"
#include <QMessageBox>

setpermission::setpermission(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setpermission)
{
    ui->setupUi(this);

    ui->setupUi(this);

    connect(ui->pb_search, &QPushButton::clicked, this, &setpermission::on_pb_search_clicked);
    connect(ui->pb_save, &QPushButton::clicked, this, &setpermission::on_pb_save_clicked);
    connect(ui->pb_out, &QPushButton::clicked, this, &setpermission::on_pb_cancel_clicked);

    // Kết nối tín hiệu selectionChanged của selection model
    connect(ui->listView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &setpermission::on_listView_itemSelectionChanged);
}

setpermission::~setpermission()
{
    delete ui;
}

void setpermission::on_pb_search_clicked()
{
    QString searchText = ui->le_fullname->text();
    performSearch(searchText);
}

void setpermission::on_pb_save_clicked()
{
    performSave();
}

void setpermission::on_pb_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận", "Bạn có chắc muốn thoát mà không lưu?", QMessageBox::Yes | QMessageBox::No);

                                                       // Kiểm tra phản hồi và đóng cửa sổ nếu cần
                                                       if (reply == QMessageBox::Yes) {
                                                           close();
                                                       }
}

void setpermission::on_listView_itemSelectionChanged()
{
    // TODO: Thực hiện chức năng khi chọn mục trong list
}

void setpermission::performSearch(const QString &searchText)
{
    // TODO: Thực hiện tìm kiếm trong cơ sở dữ liệu và cập nhật giao diện người dùng
    // Mục tiêu: Cập nhật QListWidget "listView" với kết quả tìm kiếm
}

void setpermission::performSave()
{
    // TODO: Thực hiện lưu dữ liệu vào cơ sở dữ liệu
}

void setpermission::performCancel()
{
    // TODO: Thực hiện chức năng hủy
}

void setpermission::updatePermissionList()
{
    // TODO: Thực hiện cập nhật danh sách phân quyền dựa trên lựa chọn trong list
    // Mục tiêu: Cập nhật QListWidget "lw_permission" với danh sách phân quyền mới
}
