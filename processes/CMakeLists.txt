cmake_minimum_required(VERSION 3.21)
project(extra_task)

set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utilities)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/info)

add_executable(extra_task
        main.cpp
        info/src/information_about_process.cpp
        info/information_about_process.h
        utilities/src/file_reader.cpp
        utilities/file_reader.h utilities/src/option.cpp utilities/option.h utilities/option.h info/src/many_processes.cpp info/many_processes.h)
