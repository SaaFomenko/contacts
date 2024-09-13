cmake_minimum_required(VERSION 3.30)

project(contacts)

# set exe to root dir with data files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pqxx)