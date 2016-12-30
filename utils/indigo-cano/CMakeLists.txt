cmake_minimum_required(VERSION 2.6)

project(IndigoCano)

include(DefineTest)
include_directories(../../api)

add_executable(indigo-cano main.c $<TARGET_OBJECTS:indigoObj> $<TARGET_OBJECTS:graph> $<TARGET_OBJECTS:layout> $<TARGET_OBJECTS:molecule> $<TARGET_OBJECTS:common> $<TARGET_OBJECTS:reaction>)
target_link_libraries(indigo-cano tinyxml z inchi)
if(APPLE)
	target_link_libraries(indigo-cano c++)
endif()
if(UNIX)
    set_target_properties(indigo-cano PROPERTIES LINK_FLAGS "-pthread")
endif()
pack_executable(indigo-cano)

add_test(NAME cano-simple-test COMMAND indigo-cano  - "[C@@H](N)(C)C(=O)O")
add_test(NAME cano-layered-test COMMAND indigo-cano - "[C@@H](N)(C)C(=O)O" -layered)
add_test(NAME cano-option-test COMMAND indigo-cano - "[C@@H](N)(C)C(=O)O" -no-arom -no-cistrans -no-tetrahedral)
