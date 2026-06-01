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
#cpp h
set(SRC_DIR ${CMAKE_SOURCE_DIR})
FILE(GLOB_RECURSE QRC_SOURCE_FILES 
    ${SRC_DIR}/*.qrc 
    ${SRC_DIR}/modules/*.qrc
)
list(FILTER QRC_SOURCE_FILES EXCLUDE REGEX "/(debug|release|build-)/")
file(GLOB_RECURSE SRC_SOURCE_FILES  # 非根目录下递归查找
        ${SRC_DIR}/modules/*.cpp
        ${SRC_DIR}/common/*.cpp
        ${SRC_DIR}/business/*.cpp
        ${SRC_DIR}/3rdparty/*.cpp
        )
file(GLOB_RECURSE SRC_HEADER_FILES
        ${SRC_DIR}/modules/*.h
        ${SRC_DIR}/common/*.h
        ${SRC_DIR}/business/*.h
        ${SRC_DIR}/3rdparty/*.h
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


