cmake_minimum_required(VERSION 3.18)

project(contacts)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# set Postgresql actual version.
set(PostgreSQL_ADDITIONAL_VERSIONS "15")

# set for Debian 11 postgresql 14.4 source install version.
# Commited this three sets for Windows.
set(PostgreSQL_LIBRARY "/usr/local/pgsql/lib/libpq.so.5.14")
set(PostgreSQL_INCLUDE_DIR "/usr/local/pgsql/include")
set(PostgreSQL_TYPE_INCLUDE_DIR "/usr/local/pgsql/include/libpq")
set(add_config_dir "lib/add_config")
set(add_exception_dir "")

add_subdirectory(
	"../libpqxx/libpqxx-7.7.5" libpqxx-build
)
add_subdirectory(lib)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable(${PROJECT_NAME}.exe main.cpp)

target_link_libraries(${PROJECT_NAME}.exe my_file_lib pqxx)
