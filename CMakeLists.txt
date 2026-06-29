cmake_minimum_required(VERSION 3.16)

project(StartupApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(StartupApp
    include/MainWindow.h
    include/DesktopEntryWriter.h
    src/main.cpp
    src/MainWindow.cpp
    src/DesktopEntryWriter.cpp
)

target_include_directories(StartupApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(StartupApp PRIVATE Qt5::Widgets)
