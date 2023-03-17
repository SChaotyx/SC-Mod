cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SC-Mod)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

include(cmake/CPM.cmake)

CPMAddPackage("gh:matcool/mat-dash#cdc9f70")
CPMAddPackage("gh:HJfod/cocos-headers#cbf79fc")
CPMAddPackage("gh:HJfod/gd.h#90f2110")
CPMAddPackage("gh:TsudaKageyu/minhook#4a45552")

target_compile_definitions(${PROJECT_NAME} PRIVATE CC_DLL=)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${gd.h_SOURCE_DIR}/include ${gd.h_SOURCE_DIR}
    ${minhook_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} mat-dash cocos2d minhook)
