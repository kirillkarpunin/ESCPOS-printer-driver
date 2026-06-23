cmake_minimum_required(VERSION 3.31)
project(ESCPOS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
        -Werror -Wall -Wextra -Wpedantic
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        stb
        bluetooth
)

if(BUILD_TESTING)
    enable_testing()

    add_executable(${PROJECT_NAME}-testing
        tests/ESCPOSParameterizedTest.cpp
        tests/text/TextFeatureTest.cpp
        tests/text/TextScaleTest.cpp
        tests/text/TextFontTest.cpp
        tests/text/TextRotationTest.cpp
        tests/text/TextPositionTest.cpp
        tests/image/ImageTest.cpp
    )

    target_include_directories(${PROJECT_NAME}-testing
        PRIVATE
            tests
    )

    target_link_libraries(${PROJECT_NAME}-testing
        PRIVATE
            ${PROJECT_NAME}
            GTest::gtest_main
    )

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/resources
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}-testing)
endif()