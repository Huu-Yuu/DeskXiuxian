cmake_minimum_required(VERSION 3.5)
project(DeskXiuxian)

#Ubuntu16.04 环境下使用 Qt6.12.0 GCC 64bit 编译通过
#Windows11 环境下使用 Qt6.12.0 MinGW 64bit 编译通过

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 设置Qt的qmake可执行文件路径
if(UNIX)
    # 如果是Unix系统，设置Qt的qmake可执行文件路径
    set(QT_QMAKE_EXECUTABLE "/opt/Qt6.12.0/5.12.0/gcc_64/bin/qmake")
    set(Qt6_DIR "/opt/Qt6.12.0/5.12.0/gcc_64/lib/cmake/Qt6")
    set(CMAKE_PREFIX_PATH "/opt/Qt6.12.0/5.12.0/gcc_64")
elseif(WIN32)
    # 如果是Windows系统，设置Qt的qmake可执行文件路径
    set(QT_QMAKE_EXECUTABLE "D:/Qt/6.10.2/mingw_64/bin/qmake.exe")
    set(Qt6_DIR "D:/Qt/6.10.2/mingw_64/lib/cmake/Qt6")
    set(CMAKE_PREFIX_PATH "D:/Qt/Tools/mingw1310_64")
endif()

find_package(Qt6 COMPONENTS Core Gui Sql Network Widgets WebSockets Qml Quick LinguistTools REQUIRED)

# 设置源文件列表
set(SRC_DIR ${CMAKE_SOURCE_DIR})
set(QRC_SOURCE_FILES 
    ${SRC_DIR}/img.qrc
)

# 源文件列表
set(SRC_SOURCE_FILES
    # main
    ${SRC_DIR}/modules/main.cpp
    ${SRC_DIR}/modules/main_ctrl.cpp
    
    # modules/public
    ${SRC_DIR}/modules/public/public_func.cpp
    ${SRC_DIR}/modules/public/error_display.cpp
    
    # modules/logger
    ${SRC_DIR}/modules/logger/logger.cpp
    
    # modules/server
    ${SRC_DIR}/modules/server/tcp_client.cpp
    ${SRC_DIR}/modules/server/web_socket_client.cpp
    
    # modules/filedata
    ${SRC_DIR}/modules/filedata/data_service.cpp
    ${SRC_DIR}/modules/filedata/data_service_settings.cpp
    ${SRC_DIR}/modules/filedata/data_service_remote_data.cpp
    ${SRC_DIR}/modules/filedata/role_db.cpp
    
    # modules/item
    ${SRC_DIR}/modules/item/itembase.cpp
    ${SRC_DIR}/modules/item/item_service.cpp
    
    # modules/item/prop
    ${SRC_DIR}/modules/item/prop/prop_rename_card.cpp
    ${SRC_DIR}/modules/item/prop/prop_yanshoudan10.cpp
    
    # modules/item/equip
    ${SRC_DIR}/modules/item/equip/title.cpp
    
    # modules/role
    ${SRC_DIR}/modules/role/role_player.cpp
    
    # modules/progress
    ${SRC_DIR}/modules/progress/progress_service.cpp
    
    # modules/ui
    ${SRC_DIR}/modules/ui/mainui.cpp
    ${SRC_DIR}/modules/ui/loginwindow.cpp
    ${SRC_DIR}/modules/ui/modifyrolename.cpp
    
    # modules/interface_manager
    ${SRC_DIR}/modules/interface_manager.cpp
    
    # business
    ${SRC_DIR}/business/db_manage.cpp
    ${SRC_DIR}/business/item_manage.cpp
    ${SRC_DIR}/business/progress_manage.cpp
    ${SRC_DIR}/business/role_manage.cpp
    ${SRC_DIR}/business/ui_manage.cpp
)

# 头文件列表
set(SRC_HEADER_FILES
    # common
    ${SRC_DIR}/common/singleton.h
    ${SRC_DIR}/common/sync_mechanism.h
    
    # modules/public
    ${SRC_DIR}/modules/public/public_macro.h
    ${SRC_DIR}/modules/public/public_type.h
    ${SRC_DIR}/modules/public/public_declare.h
    ${SRC_DIR}/modules/public/public_func.h
    ${SRC_DIR}/modules/public/error_code.h
    ${SRC_DIR}/modules/public/error_display.h
    
    # modules/logger
    ${SRC_DIR}/modules/logger/logger.h
    
    # modules/server
    ${SRC_DIR}/modules/server/tcp_client.h
    ${SRC_DIR}/modules/server/web_socket_client.h
    ${SRC_DIR}/modules/server/web_socket_define.h
    
    # modules/filedata
    ${SRC_DIR}/modules/filedata/data_service.h
    ${SRC_DIR}/modules/filedata/role_db.h
    
    # modules/item
    ${SRC_DIR}/modules/item/itembase.h
    ${SRC_DIR}/modules/item/item_service.h
    
    # modules/item/prop
    ${SRC_DIR}/modules/item/prop/prop_rename_card.h
    ${SRC_DIR}/modules/item/prop/prop_yanshoudan10.h
    
    # modules/item/equip
    ${SRC_DIR}/modules/item/equip/title.h
    
    # modules/role
    ${SRC_DIR}/modules/role/role_player.h
    ${SRC_DIR}/modules/role/simple_int_encryptor.h
    ${SRC_DIR}/modules/role/encrypt_int.h
    
    # modules/progress
    ${SRC_DIR}/modules/progress/progress_service.h
    
    # modules/ui
    ${SRC_DIR}/modules/ui/mainui.h
    ${SRC_DIR}/modules/ui/loginwindow.h
    ${SRC_DIR}/modules/ui/modifyrolename.h
    
    # modules/main_ctrl
    ${SRC_DIR}/modules/main_ctrl.h
    
    # modules/interface_manager
    ${SRC_DIR}/modules/interface_manager.h
    
    # business
    ${SRC_DIR}/business/db_manage.h
    ${SRC_DIR}/business/item_manage.h
    ${SRC_DIR}/business/progress_manage.h
    ${SRC_DIR}/business/role_manage.h
    ${SRC_DIR}/business/ue_manage.h
)

if(UNIX)
    message("Linux 系统")
elseif(WIN32)
    message("Windows 系统")
endif()

# 手动包含UI文件
set(UI_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/ui/mainui.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/ui/loginwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/ui/modifyrolename.ui
)
# 生成对应的头文件
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(DeskXiuxian
        ${SRC_SOURCE_FILES}
        ${SRC_HEADER_FILES}
        ${QRC_SOURCE_FILES}
        ${UI_FILES}
        ${UI_HEADERS}
)

target_include_directories(DeskXiuxian PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(DeskXiuxian PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Sql
    Qt6::Network
    Qt6::Widgets
    Qt6::WebSockets
    Qt6::Qml
    Qt6::Quick
)

# 设置翻译文件源文件
set(TRANSLATION_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/DeskXiuxian_zh_CN.ts
)

qt6_create_translation(QM_FILES ${SRC_SOURCE_FILES} ${SRC_HEADER_FILES} ${UI_FILES} ${TRANSLATION_FILES})

add_custom_target(translations ALL DEPENDS ${QM_FILES})
add_dependencies(DeskXiuxian translations)

install(TARGETS DeskXiuxian
    RUNTIME DESTINATION bin
)

set(RESOURCE_FILES
    img.qrc
)

qt6_add_resources(RESOURCE_ADDED ${RESOURCE_FILES})

target_sources(DeskXiuxian PRIVATE ${RESOURCE_ADDED})


