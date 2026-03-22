cmake_minimum_required(VERSION 3.31)
project(ESCPOS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(cmake/cpm.cmake)
include(cmake/external.cmake)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/connection/Connection.cpp
        src/connection/ComPortConnection.cpp
        src/connection/BluetoothConnection.cpp
        src/image/Image.cpp
        src/printer/Printer.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Werror -Wall -Wextra -Wpedantic -lbluetooth
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        stb
)
