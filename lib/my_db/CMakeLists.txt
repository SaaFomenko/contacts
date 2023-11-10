cmake_minimum_required(VERSION 3.18)

project(my_db 
	VERSION 1.0.0
	DESCRIPTION "C++ library with class MyFile for work with file."
	LANGUAGES CXX)

file(GLOB
	public_headers "*.h"
	sources "*.cpp")

add_library(${PROJECT_NAME}_lib ${sources} ${public_headers})
