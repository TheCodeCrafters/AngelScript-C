cmake_minimum_required( VERSION 3.24 )
project( AngelScript_C LANGUAGES CXX C )

add_subdirectory( "${CMAKE_SOURCE_DIR}/vendor/sdk/angelscript/projects/cmake" )

add_library( AngelScriptC STATIC src/angelscript_c.cpp include/angelscript/angelscript_c.h include/angelscript/jit.h)
target_include_directories( AngelScriptC PUBLIC include )
target_link_libraries( AngelScriptC angelscript )

add_subdirectory( test )
