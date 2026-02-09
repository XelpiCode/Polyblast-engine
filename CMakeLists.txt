cmake_minimum_required(VERSION 3.10)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build all libs static" FORCE)

project(Polyblast)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory("thirdparty/glfw")
add_subdirectory("thirdparty/stb_image")
add_subdirectory("thirdparty/glm")

add_library(glad STATIC "thirdparty/glad/src/gl.c")
target_include_directories(glad PUBLIC "thirdparty/glad/include")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(Polyblast ${MY_SOURCES} resources.rc)
target_include_directories(Polyblast PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(Polyblast
        PRIVATE
        glad
        glfw
        stb_image
        glm::glm-header-only
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Polyblast PUBLIC RESOURCES_PATH="./resources/")
else()
    target_compile_definitions(Polyblast PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
endif()
