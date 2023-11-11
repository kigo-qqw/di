cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(di LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options("-Wall" "-Wextra" "-Werror" "-fmodules" "-stdlib=libc++" "-v")
add_link_options("-stdlib=libc++" "-lc++abi")

add_library(di_lib)
add_library(di::di ALIAS di_lib)

target_sources(di_lib
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        di/di.cppm
        di/fwd.cppm
        di/utils.cppm
        di/resolve_dependency.cppm
        di/lifetime.cppm
        di/bean.cppm
        di/lifetime_manager.cppm
        di/service_container.cppm
        di/service_factory.cppm
)


add_subdirectory("${PROJECT_SOURCE_DIR}/tests")