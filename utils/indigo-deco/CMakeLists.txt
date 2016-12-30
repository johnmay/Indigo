cmake_minimum_required(VERSION 2.6)

project(IndigoDeco)

include(DefineTest)
include_directories(../../api ../../common)

add_executable(indigo-deco main.c $<TARGET_OBJECTS:indigoObj> $<TARGET_OBJECTS:graph> $<TARGET_OBJECTS:layout> $<TARGET_OBJECTS:molecule> $<TARGET_OBJECTS:common> $<TARGET_OBJECTS:reaction>)
target_link_libraries(indigo-deco tinyxml z inchi)
if(APPLE)
	target_link_libraries(indigo-deco c++)
endif()
if(UNIX)
    set_target_properties(indigo-deco PROPERTIES LINK_FLAGS "-pthread")
endif()
pack_executable(indigo-deco)

add_test(NAME deco-simple-test COMMAND indigo-deco -h)
