cmake_minimum_required(VERSION 3.10)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build all libs static" FORCE)

project(OPENGL_TEMPLATE_FINAL)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory("thirdparty/glfw")

add_library(glad STATIC "thirdparty/glad/src/gl.c")
target_include_directories(glad PUBLIC "thirdparty/glad/include")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(OPENGL_TEMPLATE_FINAL ${MY_SOURCES})

target_link_libraries(OPENGL_TEMPLATE_FINAL
        PRIVATE
        glad
        glfw
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(OPENGL_TEMPLATE_FINAL PUBLIC RESOURCES_PATH="./resources/")
else()
    target_compile_definitions(OPENGL_TEMPLATE_FINAL PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
endif()
