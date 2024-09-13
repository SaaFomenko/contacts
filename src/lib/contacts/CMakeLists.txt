cmake_minimum_required(VERSION 3.30)

project(contacts_lib)

# set Postgresql actual version.
set(PostgreSQL_ADDITIONAL_VERSIONS "16")

add_subdirectory("../libpqxx-7.9.2" libpqxx-build)

set(SOURCE_LIB contacts.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} pqxx)

#target_link_libraries(${PROJECT_NAME} pqxx)