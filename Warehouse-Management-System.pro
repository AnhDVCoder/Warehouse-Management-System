QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_category.cpp \
    add_product.cpp \
    add_supplier.cpp \
    dangxuat.cpp \
    export_product.cpp \
    import_product.cpp \
    login.cpp \
    main.cpp \
    modify_product.cpp \
    modify_supplier.cpp \
    nguoidung.cpp \
    overview.cpp \
    phanquyen.cpp \
    quan_li_dai_li.cpp \
    quan_li_nguoi_dung.cpp \
    report.cpp \
    sua_nguoi_dung.cpp \
    them_dai_ly.cpp \
    themnguoi.cpp

HEADERS += \
    add_category.h \
    add_product.h \
    add_supplier.h \
    dangxuat.h \
    export_product.h \
    import_product.h \
    login.h \
    modify_product.h \
    modify_supplier.h \
    nguoidung.h \
    overview.h \
    phanquyen.h \
    quan_li_dai_li.h \
    quan_li_nguoi_dung.h \
    report.h \
    sql.h \
    sua_nguoi_dung.h \
    them_dai_ly.h \
    themnguoi.h

FORMS += \
    add_category.ui \
    add_nguoi.ui \
    add_product.ui \
    add_supplier.ui \
    dangxuat.ui \
    export_product.ui \
    import_product.ui \
    login.ui \
    modify_product.ui \
    modify_supplier.ui \
    nguoidung.ui \
    overview.ui \
    phanquyen.ui \
    quan_li_dai_li.ui \
    quan_li_nguoi_dung.ui \
    report.ui \
    sua_nguoi_dung.ui \
    them_dai_ly.ui \
    themnguoi.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
