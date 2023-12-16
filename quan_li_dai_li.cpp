#include "quan_li_dai_li.h"
#include "ui_quan_li_dai_li.h"
#include <QMessageBox>
quan_li_dai_li::quan_li_dai_li(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::quan_li_dai_li),
    model(new QStringListModel(this)),
    listView(new QListView(this))
{
    ui->setupUi(this);
    loadDaiLiListView();

    connect(ui->pb_thoat_dl, &QPushButton::clicked, this, &quan_li_dai_li::on_pb_thoat_dl_clicked);
    connect(ui->pb_xoa_dl1, &QPushButton::clicked, this, &quan_li_dai_li::on_pb_xoa_dl_clicked);
    connect(ui->pb_timkiem_DL, &QPushButton::clicked, this, &quan_li_dai_li::on_pb_timkiem_dl_clicked);
    connect(listView, &QListView::clicked, this, &quan_li_dai_li::on_listView_clicked);
    connect(ui->pb_sua_dl, &QPushButton::clicked, this, &quan_li_dai_li::on_pb_sua_dl_save);

    listView->setModel(model);

    // Thêm listView vào layout hoặc UI của bạn nếu cần thiết
    ui->layoutWidget_3->layout()->addWidget(listView);
}

quan_li_dai_li::~quan_li_dai_li()
{
    delete ui;
}
void quan_li_dai_li::timKiemDaiLi(const QString &tuKhoa)
{
    // Xóa các dòng hiện tại trong bảng
    model->setStringList(QStringList());

    // Thực hiện truy vấn tìm kiếm
    QSqlQuery query;
    query.prepare("SELECT * FROM dai_ly WHERE tenDL LIKE :tuKhoa OR maDL LIKE :tuKhoa");
    query.bindValue(":tuKhoa", "%" + tuKhoa + "%");

    if (query.exec()) {
        // Lặp qua kết quả truy vấn và thêm vào model
        QStringList danhSachDaiLi;
        while (query.next()) {
            QString maDL = query.value(0).toString();
            QString tenDL = query.value(1).toString();
            QString dia_chi = query.value(2).toString();

            QString sdtDL = query.value(3).toString();
            QString email = query.value(4).toString();
            // QString maHD = query.value(5).toString();
            QString DLInfo = QString("%1, %2, %3, %4, %5").arg(maDL,tenDL, dia_chi, sdtDL, email);
            danhSachDaiLi << DLInfo;
        }
        // Cập nhật model với danh sách đại lí
        model->setStringList(danhSachDaiLi);
    } else {
        // Xử lý lỗi truy vấn
        QMessageBox::critical(this, "Lỗi", "Không thể tìm kiếm. Lỗi: " + query.lastError().text());
    }
}

void quan_li_dai_li::on_pb_timkiem_dl_clicked()
{
    QString tuKhoa = ui->le_tukhoaDL->text();  // Sửa từ pb_timkiem_2 thành le_tukhoa
    timKiemDaiLi(tuKhoa);
}

void quan_li_dai_li::on_pb_xoa_dl_clicked()
{
    // Kiểm tra nếu đại lí đã chọn
    if (!selectedDL.isEmpty()) {
        // Thực hiện xóa đại lí trong cơ sở dữ liệu
        QSqlQuery query;

        query.prepare("DELETE FROM dai_ly WHERE maDL like :maDL");
        query.bindValue(":maDL", id);

        if (query.exec()) {
            // Hiển thị thông báo thành công
            QMessageBox::information(this, "Thông báo", "Xóa đại lí thành công! ");

            // Cập nhật lại ListView sau khi xóa
            loadDaiLiListView();
        } else {
            // Xử lý lỗi truy vấn
            QMessageBox::critical(this, "Lỗi", "Không thể xóa đại lí. Lỗi: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn đại lí cần xóa.");
    }
}

void quan_li_dai_li::on_pb_thoat_dl_clicked()
{
    close();
}

void quan_li_dai_li::loadDaiLiListView()
{
    // TODO: Load danh sách đại lí từ cơ sở dữ liệu hoặc nguồn dữ liệu tương ứng
    // và thêm vào model
    QStringList danhSachDaiLi; // Thay bằng danh sách thực tế từ cơ sở dữ liệu
    danhSachDaiLi << "Đại lí 1" << "Đại lí 2" << "Đại lí 3";

    model->setStringList(danhSachDaiLi);
}

void quan_li_dai_li::on_listView_clicked(const QModelIndex &index)
{
    // Lấy thông tin đại lí được chọn từ QListView
    selectedDL = model->data(index, Qt::DisplayRole).toString();
    int x = 0;
    for(int i = 0; i < selectedDL.size(); i ++) {
        if(selectedDL.at(i) == ',') {
            x = i;
            break;
        }
    }
    id = selectedDL.left(x);
    // ui->le_maND_s->setText(id);
}

void quan_li_dai_li::on_pb_sua_dl_save() {


if (!selectedDL.isEmpty()) {
        // Lấy mã đại lí từ dòng được chọn
        int x = 0;
        for (int i = 0; i < selectedDL.size(); i++) {
            if (selectedDL.at(i) == ',') {
                x = i;
                break;
            }
        }
        id = selectedDL.left(x);

        // Hiển thị tất cả đại lí người dùng khi nhấn nút "Sửa"
        QSqlQuery query;
        query.prepare("SELECT * FROM dai_ly WHERE maDL = :maDL");
        query.bindValue(":maDL", id);

        if (query.exec() && query.next()) {
            QString tenDL = query.value(1).toString();
            QString dia_chi = query.value(2).toString();
            QString sdtDL = query.value(3).toString();
            QString email = query.value(4).toString();
            QString maHD = query.value(5).toString();

            // Hiển thị thông tin lên các QLineEdit
            ui->le_maDL->setText(id);
            ui->le_tenDL->setText(tenDL);
            ui->le_dia_chiDL->setText(dia_chi);
            ui->le_sdtDL->setText(sdtDL);
            ui->le_email_DL->setText(email);
            // ui->le_maHD->setText(maHD);

            // Thêm các dòng hiển thị thông tin khác ở đây nếu cần
        } else {
            // Xử lý lỗi truy vấn
            QMessageBox::critical(this, "Lỗi", "Không thể lấy thông tin đại lí. Lỗi: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn đại lí cần sửa.");
    }
}

void quan_li_dai_li::on_pb_sua_dl_save_clicked() {
    QString maDL = ui->le_maDL->text();
    QString tenDL = ui->le_tenDL->text();
    QString dia_chi = ui->le_dia_chiDL->text();
    QString sdtDL = ui->le_sdtDL->text();
    QString email = ui->le_email_DL->text();
    // QString maHD = ui->le_maHD->text();


    QSqlQuery query;
    query.prepare("UPDATE dai_ly SET tenDL = :tenDL, dia_chi = :dia_chi, sdtDL = :sdtDL, email = :mail, maHD = :maHD WHERE maDL = :maDL");
    query.bindValue(":tenDL", tenDL);
    query.bindValue(":dia_chi", dia_chi);
    query.bindValue(":sdtDL", sdtDL);
    query.bindValue(":email", email);
    // query.bindValue(":maHD", maHD);

    query.bindValue(":maDL", id);

    if (query.exec()) {
        // Hiển thị thông báo thành công
        QMessageBox::information(this, "Thông báo", "Thay đổi thông tin đại lí thành công! ");
    } else {
        // Xử lý lỗi truy vấn
        QMessageBox::critical(this, "Lỗi", "Không thể thay đổi thông tin đại lí. Lỗi: " + query.lastError().text());
    }
}
