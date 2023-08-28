QT       += core gui
QT += sql
QT += core

LIBS += -L"D:/source code/DeskXiuxian/bin" -lmysql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filedata/datamanage.cpp \
    game_progress/gameprogress.cpp \
    item/itembase.cpp \
    item/itemsystem.cpp \
    logger/logger.cpp \
    main.cpp \
    mainctrl.cpp \
    mainui.cpp \
    role/rolesystem.cpp \
    ui/loginwindow.cpp \
    filedata/datamanage_settings.cpp \
    filedata/datamanage_remote_data.cpp \
    ui/modifyrolename.cpp \
    public/public_func.cpp \
    server/tcp_client.cpp

HEADERS += \
    filedata/datamanage.h \
    game_progress/gameprogress.h \
    item/itembase.h \
    item/itemsystem.h \
    logger/logger.h \
    mainctrl.h \
    mainui.h \
    public/public_macro.h \
    public/public_type.h \
    role/rolesystem.h \
    ui/loginwindow.h \
    ui/modifyrolename.h \
    public/public_func.h \
    public/error_code.h \
    server/tcp_client.h

FORMS += \
    mainui.ui \
    ui/loginwindow.ui \
    ui/modifyrolename.ui

TRANSLATIONS += \
    DeskXiuxian_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    img.qrc
