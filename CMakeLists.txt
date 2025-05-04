cmake_minimum_required(VERSION 3.16)

project(snake_game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    snakegame.cpp
    snakegame.h
    snake.cpp
    snake.h
    food.cpp
    food.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(snake_game
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(snake_game
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(snake_game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 设置Windows可执行文件属性
set_target_properties(snake_game PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(snake_game)
endif()
