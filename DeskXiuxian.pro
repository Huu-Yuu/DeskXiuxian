QT += core gui
QT += sql
QT += core
QT += network
QT += websockets

#LIBS += -L"D:/source code/DeskXiuxian/bin" -lmysql
LIBS += -luser32 -lkernel32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#DEFINES += _BUILDING_APP
#include($$PWD/3rdparty/include/QxOrm/QxOrm.pri)
#INCLUDEPATH += $$PWD/3rdparty/include/QxOrm/include
##添加编译好的动态库，QxOrm源码编译的动态库在QxOrm/lib目录中，最好编译debug、release两个版本
#LIBS += -L$$PWD/3rdparty/include/QxOrm/lib
#CONFIG(debug, debug|release) {
#LIBS += -lQxOrmd
#} else {
#LIBS +=  -lQxOrm
#}

SOURCES += \
    modules/filedata/data_service_remote_data.cpp \
    modules/filedata/data_service_settings.cpp \
    modules/filedata/role_db.cpp \
    modules/progress/progress_service.cpp \
    modules/item/itembase.cpp \
    modules/item/item_service.cpp \
    modules/item/equip/title.cpp \
    modules/item/prop/prop_rename_card.cpp \
    modules/item/prop/prop_yanshoudan10.cpp \
    modules/logger/logger.cpp \
    main.cpp \
    main_ctrl.cpp \
    modules/ui/mainui.cpp \
    modules/ui/loginwindow.cpp \
    modules/ui/modifyrolename.cpp \
    modules/role/role_player.cpp \
    modules/filedata/data_service.cpp \
    modules/public/public_func.cpp \
    modules/public/error_display.cpp \
    modules/server/tcp_client.cpp \
    modules/server/web_socket_client.cpp \
    business/progress_manage.cpp \
    business/db_manage.cpp \
    business/item_manage.cpp \
    business/role_manage.cpp \
    business/ui_manage.cpp

HEADERS += \
    common/singleton.h \
    modules/filedata/data_service.h \
    modules/filedata/role_db.h \
    modules/progress/progress_service.h \
    modules/item/item_service.h \
    modules/item/equip/title.h \
    modules/item/prop/prop_rename_card.h \
    modules/item/prop/prop_yanshoudan10.h \
    modules/logger/logger.h \
    main_ctrl.h \
    modules/ui/mainui.h \
    modules/ui/loginwindow.h \
    modules/ui/modifyrolename.h \
    modules/ui/ui_manage.h \
    modules/public/public_macro.h \
    modules/public/public_type.h \
    modules/public/public_declare.h \
    modules/role/role_player.h \
    modules/role/simple_int_encryptor.h \
    modules/role/encrypt_int.h \
    modules/public/public_func.h \
    modules/public/error_code.h \
    modules/public/error_display.h \
    modules/server/tcp_client.h \
    modules/server/web_socket_client.h \
    modules/server/web_socket_define.h \
    modules/interface_manager.h \
    business/progress_manage.h \
    business/db_manage.h \
    business/item_manage.h \
    business/role_manage.h \
    business/ui_manage.h

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
