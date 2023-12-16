#include "quan_li_nguoi_dung.h"
#include "ui_quan_li_nguoi_dung.h"
#include <QMessageBox>

xoa_nguoi_dung::xoa_nguoi_dung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xoa_nguoi_dung),
    model(new QStringListModel(this)),
    listView(new QListView(this))
{
    ui->setupUi(this);
    loadNguoiDungListView();

    connect(ui->pb_thoat_nd, &QPushButton::clicked, this, &xoa_nguoi_dung::on_pb_thoat_nd_clicked);
    connect(ui->pb_xoa_nd, &QPushButton::clicked, this, &xoa_nguoi_dung::on_pb_xoa_nd_clicked);
    connect(ui->pb_timkiem_2, &QPushButton::clicked, this, &xoa_nguoi_dung::on_pb_timkiem_nd_clicked);
    connect(listView, &QListView::clicked, this, &xoa_nguoi_dung::on_listView_clicked);
    connect(ui->pb_sua_nd, &QPushButton::clicked, this, &xoa_nguoi_dung::on_pb_sua_nd_save);

    listView->setModel(model);

    // Thêm listView vào layout hoặc UI của bạn nếu cần thiết
    ui->layoutWidget_3->layout()->addWidget(listView);
}

xoa_nguoi_dung::~xoa_nguoi_dung()
{
    delete ui;
}

void xoa_nguoi_dung::timKiemNguoiDung(const QString &tuKhoa)
{
    // Xóa các dòng hiện tại trong bảng
    model->setStringList(QStringList());

    // Thực hiện truy vấn tìm kiếm
    QSqlQuery query;
    query.prepare("SELECT * FROM nguoi_dung WHERE tenND LIKE :tuKhoa OR username LIKE :tuKhoa");
    query.bindValue(":tuKhoa", "%" + tuKhoa + "%");

    if (query.exec()) {
        // Lặp qua kết quả truy vấn và thêm vào model
        QStringList danhSachNguoiDung;
        while (query.next()) {
            QString maND = query.value(0).toString();
            QString tenND = query.value(1).toString();
            QString username = query.value(2).toString();
           // QString matkhau = query.value(2).toString();
            QString sdtND = query.value(4).toString();
            QString email = query.value(5).toString();
            QString dia_chi = query.value(6).toString();
            QString userInfo = QString("%1, %2, %3, %4, %5, %6").arg(maND,tenND, username, sdtND, email, dia_chi);
            danhSachNguoiDung << userInfo;
        }
        // Cập nhật model với danh sách người dùng
        model->setStringList(danhSachNguoiDung);
    } else {
        // Xử lý lỗi truy vấn
        QMessageBox::critical(this, "Lỗi", "Không thể tìm kiếm. Lỗi: " + query.lastError().text());
    }
}

void xoa_nguoi_dung::on_pb_timkiem_nd_clicked()
{
    QString tuKhoa = ui->le_tukhoa->text();  // Sửa từ pb_timkiem_2 thành le_tukhoa
    timKiemNguoiDung(tuKhoa);
}

void xoa_nguoi_dung::on_pb_xoa_nd_clicked()
{
    // Kiểm tra nếu người dùng đã chọn
    if (!selectedUser.isEmpty()) {
        // Thực hiện xóa người dùng trong cơ sở dữ liệu
        QSqlQuery query;

        query.prepare("DELETE FROM nguoi_dung WHERE maND like :maND");
        query.bindValue(":maND", id);

        if (query.exec()) {
            // Hiển thị thông báo thành công
            QMessageBox::information(this, "Thông báo", "Xóa người dùng thành công! " + id);

            // Cập nhật lại ListView sau khi xóa
            loadNguoiDungListView();
        } else {
            // Xử lý lỗi truy vấn
            QMessageBox::critical(this, "Lỗi", "Không thể xóa người dùng. Lỗi: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn người dùng cần xóa.");
    }
}

void xoa_nguoi_dung::on_pb_thoat_nd_clicked()
{
    close();
}

void xoa_nguoi_dung::loadNguoiDungListView()
{
    // TODO: Load danh sách người dùng từ cơ sở dữ liệu hoặc nguồn dữ liệu tương ứng
    // và thêm vào model
    QStringList danhSachNguoiDung; // Thay bằng danh sách thực tế từ cơ sở dữ liệu
    danhSachNguoiDung << "Người Dùng 1" << "Người Dùng 2" << "Người Dùng 3";

    model->setStringList(danhSachNguoiDung);
}

void xoa_nguoi_dung::on_listView_clicked(const QModelIndex &index)
{
    // Lấy thông tin người dùng được chọn từ QListView
    selectedUser = model->data(index, Qt::DisplayRole).toString();
    int x = 0;
    for(int i = 0; i < selectedUser.size(); i ++) {
        if(selectedUser.at(i) == ',') {
            x = i;
            break;
        }
    }
    id = selectedUser.left(x);
    // ui->le_maND_s->setText(id);
}

void xoa_nguoi_dung::on_pb_sua_nd_save() {


if (!selectedUser.isEmpty()) {
        // Lấy mã người dùng từ dòng được chọn
        int x = 0;
        for (int i = 0; i < selectedUser.size(); i++) {
            if (selectedUser.at(i) == ',') {
                x = i;
                break;
            }
        }
        id = selectedUser.left(x);

        // Hiển thị tất cả thông tin người dùng khi nhấn nút "Sửa"
        QSqlQuery query;
        query.prepare("SELECT * FROM nguoi_dung WHERE maND = :maND");
        query.bindValue(":maND", id);

        if (query.exec() && query.next()) {
            QString tenND = query.value(1).toString();
            QString username = query.value(2).toString();
            QString matkhau = query.value(3).toString();
            QString sdtND = query.value(4).toString();
            QString email = query.value(5).toString();
            QString dia_chi = query.value(6).toString();

            // Hiển thị thông tin lên các QLineEdit
            ui->le_maND_s->setText(id);
            ui->le_tenND_s->setText(tenND);
            ui->le_username_s->setText(username);
            ui->le_password_s->setText(matkhau);
            ui->le_sdtND_s->setText(sdtND);
            ui->le_email_nd->setText(email);
            ui->le_dia_chi_s->setText(dia_chi);
            // Thêm các dòng hiển thị thông tin khác ở đây nếu cần
        } else {
            // Xử lý lỗi truy vấn
            QMessageBox::critical(this, "Lỗi", "Không thể lấy thông tin người dùng. Lỗi: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn người dùng cần sửa.");
    }
}

void xoa_nguoi_dung::on_pb_sua_nd_save_clicked() {
    QString tenND = ui->le_tenND_s->text();
    QString username = ui->le_username_s->text();
    QString password = ui->le_password_s->text();
    QString sdtND = ui->le_sdtND_s->text();
    QString email = ui->le_email_nd->text();
    QString dia_chi = ui->le_dia_chi_s->text();

    QSqlQuery query;
    query.prepare("UPDATE nguoi_dung SET tenND = :tenND, username = :username, password = :pass, sdtND = :sdt, email = :mail, dia_chi = :adr WHERE maND = :maND");
    query.bindValue(":tenND", tenND);
    query.bindValue(":username", username);
    query.bindValue(":pass", password);
    query.bindValue(":sdt", sdtND);
    query.bindValue(":mail", email);
    query.bindValue(":adr", dia_chi);
    query.bindValue(":maND", id);

    if (query.exec()) {
        // Hiển thị thông báo thành công
        QMessageBox::information(this, "Thông báo", "Thay đổi thông tin người dùng thành công! ");
    } else {
        // Xử lý lỗi truy vấn
        QMessageBox::critical(this, "Lỗi", "Không thể thay đổi thông tin người dùng. Lỗi: " + query.lastError().text());
    }
}
