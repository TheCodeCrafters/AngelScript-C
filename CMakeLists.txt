cmake_minimum_required(VERSION 3.21)
project(AngelScript_C)

set(CMAKE_CXX_STANDARD 17)

add_library(
		AngelScript_C SHARED
		include/AngelScript_c.h
		src/AngelScript_c.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/AngelScript/angelscript/projects/cmake angelscript)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/AngelScript/angelscript/include)
target_link_libraries(AngelScript_C ${ANGELSCRIPT_LIBRARY_NAME})
