cmake_minimum_required(VERSION 3.5)

project(qMCS_gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES qMCS_gui_zh_CN.ts)
set(RESOURCES mcs_resource.qrc)

add_executable(qMCS_gui
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${TS_FILES}
    ${RESOURCES}
  )

target_link_libraries(qMCS_gui PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
