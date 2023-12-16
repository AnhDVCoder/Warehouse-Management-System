
#include "dangxuat.h"
#include <QPushButton>
#include <QVBoxLayout>

dangxuat::dangxuat(QWidget *parent) :
    QDialog(parent)
{
    // Tạo các nút
    okButton = new QPushButton("Đồng ý", this);
    cancelButton = new QPushButton("Hủy bỏ", this);

    // Kết nối sự kiện click với phương thức acceptLogout
    connect(okButton, &QPushButton::clicked, this, &dangxuat::on_buttonBox_accepted);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    // Tạo layout và thiết lập các nút
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    // Thiết lập các thuộc tính của cửa sổ
    setWindowTitle("Xác nhận Đăng xuất");
    setModal(true);
}

dangxuat::~dangxuat()
{
    // Không cần giải phóng nút vì chúng sẽ tự động được giải phóng khi đối tượng cha được giải phóng
}

void dangxuat::on_buttonBox_accepted()
{
    // Khi người dùng chọn "Đồng ý", gọi accept để đóng cửa sổ và thông báo rằng đăng xuất đã được chấp nhận
    accept();
}
