# CMake version expected
cmake_minimum_required(VERSION 3.18)

# Project title
project(FT_BASE_LIB)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify source file directories
set(DIR_SRC "${FT_BASE_LIB_SOURCE_DIR}/src")
set(DIR_BUILD "${DIR_SRC}/build")
set(DIR_ERROR "${DIR_SRC}/error")
set(DIR_HANDLE "${DIR_SRC}/handle")
set(DIR_THREAD "${DIR_SRC}/thread")
set(DIR_TRAITS "${DIR_SRC}/traits")

# source files

file (GLOB CPP_FULL "")
file (GLOB HPP_FULL "")

# source : main
# set(SRC_MAIN "${DIR_SRC}/main.cpp")
# source_group("source" FILES ${SRC_MAIN})
# file (GLOB CPP_FULL ${SRC_MAIN})
# file (GLOB HPP_FULL "")

# source : build
file(GLOB_RECURSE SRC_BUILD_CPP ${DIR_BUILD}/*.cpp)
file(GLOB_RECURSE SRC_BUILD_HPP ${DIR_BUILD}/*.h ${DIR_BUILD}/*.hpp)
source_group("source\\build" FILES ${SRC_BUILD_CPP})
source_group("header\\build" FILES ${SRC_BUILD_HPP})
list (APPEND CPP_FULL ${SRC_BUILD_CPP})
list (APPEND HPP_FULL ${SRC_BUILD_HPP})

# source : error
file(GLOB_RECURSE SRC_ERROR_CPP ${DIR_ERROR}/*.cpp)
file(GLOB_RECURSE SRC_ERROR_HPP ${DIR_ERROR}/*.h ${DIR_ERROR}/*.hpp)
source_group("source\\error" FILES ${SRC_ERROR_CPP})
source_group("header\\error" FILES ${SRC_ERROR_HPP})
list (APPEND CPP_FULL ${SRC_ERROR_CPP})
list (APPEND HPP_FULL ${SRC_ERROR_HPP})

# source : handle
file(GLOB_RECURSE SRC_HANDLE_CPP ${DIR_HANDLE}/*.cpp)
file(GLOB_RECURSE SRC_HANDLE_HPP ${DIR_HANDLE}/*.h ${DIR_HANDLE}/*.hpp)
source_group("source\\handle" FILES ${SRC_HANDLE_CPP})
source_group("header\\handle" FILES ${SRC_HANDLE_HPP})
list (APPEND CPP_FULL ${SRC_HANDLE_CPP})
list (APPEND HPP_FULL ${SRC_HANDLE_HPP})

# source : thread
file(GLOB_RECURSE SRC_THREAD_CPP ${DIR_THREAD}/*.cpp)
file(GLOB_RECURSE SRC_THREAD_HPP ${DIR_THREAD}/*.h ${DIR_THREAD}/*.hpp)
source_group("source\\thread" FILES ${SRC_THREAD_CPP})
source_group("header\\thread" FILES ${SRC_THREAD_HPP})
list (APPEND CPP_FULL ${SRC_THREAD_CPP})
list (APPEND HPP_FULL ${SRC_THREAD_HPP})

# source : traits
file(GLOB_RECURSE SRC_TRAITS_CPP ${DIR_TRAITS}/*.cpp)
file(GLOB_RECURSE SRC_TRAITS_HPP ${DIR_TRAITS}/*.h ${DIR_TRAITS}/*.hpp)
source_group("source\\traits" FILES ${SRC_TRAITS_CPP})
source_group("header\\traits" FILES ${SRC_TRAITS_HPP})
list (APPEND CPP_FULL ${SRC_TRAITS_CPP})
list (APPEND HPP_FULL ${SRC_TRAITS_HPP})

# include the files
add_library(FT_BASE_LIB ${CPP_FULL} ${HPP_FULL})
set_target_properties(FT_BASE_LIB PROPERTIES OUTPUT_NAME ft_base_lib)

# define default include path
target_include_directories(FT_BASE_LIB PRIVATE "${DIR_SRC}")

