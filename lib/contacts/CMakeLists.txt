cmake_minimum_required(VERSION 3.30)

project(contacts 
	VERSION 1.0.0
	DESCRIPTION "C++ library with class Contacts for work with database contacts."
	LANGUAGES CXX)

file(GLOB
	public_headers "*.h"
	sources "*.cpp")

add_library(${PROJECT_NAME}_lib ${sources} ${public_headers})
