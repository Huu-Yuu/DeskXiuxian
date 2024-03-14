QT += core gui
QT += sql
QT += core
QT += network

#LIBS += -L"D:/source code/DeskXiuxian/bin" -lmysql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    modules/game_progress/game_progress.cpp \
    modules/game_progress/progress_system.cpp \
    modules/item/itembase.cpp \
    modules/item/item_system.cpp \
    modules/item/item_manage.cpp \
    modules/item/prop/prop_rename_card.cpp \
    modules/logger/logger.cpp \
    main.cpp \
    main_ctrl.cpp \
    modules/ui/mainui.cpp \
    modules/ui/loginwindow.cpp \
    modules/ui/modifyrolename.cpp \
    modules/role/role_system.cpp \
    modules/role/role_player.cpp \
    modules/filedata/datamanage_settings.cpp \
    modules/filedata/datamanage_remote_data.cpp \
    modules/filedata/db_system.cpp \
    modules/filedata/data_manage.cpp \
    modules/public/public_func.cpp \
    modules/server/tcp_client.cpp \
    modules/interface_manager.cpp

HEADERS += \
    common/singleton.h \
    modules/filedata/data_manage.h \
    modules/filedata/db_system.h \
    modules/game_progress/game_progress.h \
    modules/game_progress/progress_system.h \
    modules/item/itembase.h \
    modules/item/item_system.h \
    modules/item/item_manage.h \
    modules/item/prop/prop_rename_card.h \
    modules/logger/logger.h \
    main_ctrl.h \
    modules/ui/mainui.h \
    modules/public/public_macro.h \
    modules/public/public_type.h \
    modules/public/public_declare.h \
    modules/role/role_system.h \
    modules/role/role_player.h \
    modules/ui/loginwindow.h \
    modules/ui/modifyrolename.h \
    modules/public/public_func.h \
    modules/public/error_code.h \
    modules/server/tcp_client.h \
    modules/interface_manager.h

FORMS += \
    modules/ui/mainui.ui \
    modules/ui/loginwindow.ui \
    modules/ui/modifyrolename.ui

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
