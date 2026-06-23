CPMAddPackage(
    NAME stb
    GITHUB_REPOSITORY nothings/stb
    GIT_TAG f1c79c02822848a9bed4315b12c8c8f3761e1296
    DOWNLOAD_ONLY YES
)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})

if(BUILD_TESTING)
    CPMAddPackage(
        NAME googletest
        GITHUB_REPOSITORY google/googletest
        GIT_TAG v1.17.0
        EXCLUDE_FROM_ALL YES
        OPTIONS
            "INSTALL_GTEST OFF"
            "gtest_build_tests OFF"
            "gmock_build_tests OFF"
    )
endif()