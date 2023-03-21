add_executable( testing src/test.c )
target_include_directories( testing PRIVATE ../include )
target_link_libraries( testing PRIVATE AngelScriptC )