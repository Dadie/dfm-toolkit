cmake_minimum_required(VERSION 3.14)
include(CheckIPOSupported)
check_ipo_supported(RESULT lto_supported)

# Project Information
project (dfm-find VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  docopt
  GIT_REPOSITORY https://github.com/docopt/docopt.cpp.git
  GIT_TAG "origin/master"
)
FetchContent_MakeAvailable(docopt)

# Source
set (SOURCES
    "src/${PROJECT_NAME}.main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} PUBLIC docopt)
target_link_libraries(${PROJECT_NAME} PUBLIC libdfm)

# Set compiler options
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
target_compile_options(${PROJECT_NAME} PRIVATE "-Wpedantic")
target_compile_options(${PROJECT_NAME} PRIVATE "-Wextra")
target_compile_options(${PROJECT_NAME} PRIVATE "-pthread")
target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC")
target_compile_options(${PROJECT_NAME} PRIVATE "-O3")

if(lto_supported)
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif(lto_supported)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
