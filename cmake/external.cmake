CPMAddPackage(
    NAME stb
    GITHUB_REPOSITORY nothings/stb
    GIT_TAG f1c79c02822848a9bed4315b12c8c8f3761e1296
    DOWNLOAD_ONLY YES
)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})