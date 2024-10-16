cmake_minimum_required(VERSION 3.5)
project(DeskXiuxina)

#Ubuntu16.04 环境下使用 Qt5.12.0 GCC 64bit 编译通过

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
    set(QT_QMAKE_EXECUTABLE "/opt/Qt5.12.0/5.12.0/gcc_64/bin/qmake")
    set(Qt5_DIR "/opt/Qt5.12.0/5.12.0/gcc_64/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "/opt/Qt5.12.0/5.12.0/gcc_64")
elseif(WIN32)
    # 如果是Windows系统，设置Qt的qmake可执行文件路径
    set(QT_QMAKE_EXECUTABLE "D:/Qt/Qt5.12.12/5.12.12/msvc2017/bin/qmake.exe")
    set(Qt5_DIR "D:/Qt/Qt5.12.12/5.12.12/msvc2017/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.12.12/5.12.12/msvc2017")
endif()

find_package(Qt5 COMPONENTS Core Gui Sql Network Widgets WebSockets Qml Quick REQUIRED)

# 设置源文件列表
#cpp h
set(SRC_DIR ${CMAKE_SOURCE_DIR})
file(GLOB_RECURSE SRC_SOURCE_FILES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE SRC_HEADER_FILES ${SRC_DIR}/*.h)
FILE(GLOB_RECURSE QRC_SOURCE_FILES ${SRC_DIR}/*.qrc)

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
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(DeskXiuxina
        ${SRC_SOURCE_FILES}
        ${SRC_HEADER_FILES}
        ${QRC_SOURCE_FILES}
        ${UI_FILES}
        ${UI_HEADERS}
)

target_include_directories(DeskXiuxina PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(DeskXiuxina PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Network
    Qt5::Widgets
    Qt5::WebSockets
    Qt5::Qml
    Qt5::Quick
)

#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} DeskXiuxian_zh_CN.ts)
# 设置翻译文件源文件
set(TRANSLATION_FILES
        ${CMAKE_SOURCE_DIR}/DeskXiuxian_zh_CN.ts
        )

install(TARGETS DeskXiuxina
    RUNTIME DESTINATION bin
)

set(RESOURCE_FILES
    img.qrc
)

qt5_add_resources(RESOURCE_ADDED ${RESOURCE_FILES})

target_sources(DeskXiuxina PRIVATE ${RESOURCE_ADDED})


