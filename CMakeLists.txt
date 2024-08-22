cmake_minimum_required(VERSION 3.30)

set( CMAKE_CXX_COMPILER "C:\\msys64\\ucrt64\\bin\\g++.exe" )

set( CMAKE_C_COMPILER "C:\\msys64\\ucrt64\\bin\\gcc.exe" )

project(contacts)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# set Postgresql actual version.
set(PostgreSQL_ADDITIONAL_VERSIONS "16")

add_subdirectory(
	"../libpqxx-7.9.2" libpqxx-build
)
add_subdirectory(lib)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable(${PROJECT_NAME}.exe main.cpp)

target_link_libraries(${PROJECT_NAME}.exe my_file_lib pqxx)