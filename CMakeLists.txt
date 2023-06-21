cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SC-Mod)

if (${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
  add_compile_definitions(SHOW_CONSOLE)
endif()

include(cmake/CPM.cmake)

CPMAddPackage("gh:matcool/mat-dash#294126a")
CPMAddPackage("gh:HJfod/cocos-headers#1ec524e")
CPMAddPackage("gh:SChaotyx/gd.h#2ee1f0b")
CPMAddPackage("gh:TsudaKageyu/minhook#98b74f1")
CPMAddPackage("gh:btzy/nativefiledialog-extended#06a5c1f")


file(GLOB_RECURSE SOURCE_FILES
    src/*.cpp
    ${nativefiledialog-extended_SOURCE_DIR}/src/nfd_common.c
    ${nativefiledialog-extended_SOURCE_DIR}/src/nfd_win.cpp
    )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE CC_DLL=)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${gd.h_SOURCE_DIR}/include ${gd.h_SOURCE_DIR}
    ${minhook_SOURCE_DIR}/include
    ${nativefiledialog-extended_SOURCE_DIR}/src/include
)

target_link_libraries(${PROJECT_NAME} mat-dash cocos2d minhook)
