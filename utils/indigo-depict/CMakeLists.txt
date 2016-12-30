cmake_minimum_required(VERSION 2.6)

project(IndigoDepict)

include(DefineTest)


include_directories(../../api ../../api/plugins/renderer ../../common)
include_directories(${IndigoRenderer_SOURCE_DIR} ${Indigo_SOURCE_DIR} ${Indigo_SOURCE_DIR}/src ${Cairo_SOURCE_DIR} ${Common_SOURCE_DIR} ${Common_SOURCE_DIR}/..)

add_executable(indigo-depict main.c $<TARGET_OBJECTS:render2d> $<TARGET_OBJECTS:indigo-renderer-Obj> $<TARGET_OBJECTS:indigoObj> $<TARGET_OBJECTS:graph> $<TARGET_OBJECTS:layout> $<TARGET_OBJECTS:molecule> $<TARGET_OBJECTS:common> $<TARGET_OBJECTS:reaction>)
target_link_libraries(indigo-depict cairo png pixman inchi tinyxml z)
if(APPLE)
	INCLUDE(GetSystemVersion)
	INCLUDE(MacFrameworks)
	FIND_FRAMEWORK(ApplicationServices)
	target_link_libraries(indigo-depict c++ ${FRAMEWORK_ApplicationServices})
	SET_TARGET_PROPERTIES(indigo-depict PROPERTIES LINK_FLAGS "${LINK_FLAGS} -Xlinker -framework -Xlinker ApplicationServices")
endif()
if(UNIX)
    set_target_properties(indigo-depict PROPERTIES LINK_FLAGS "-pthread")
endif()
pack_executable(indigo-depict)

add_test(NAME depict-simple-test COMMAND indigo-depict - "[CH2:1]=[CH:2][CH2:1][CH2:3][C:4](C)[CH2:3]" output.png)
add_test(NAME depict-query-test COMMAND indigo-depict - "CC.[O-][*-]([O-])=O" query.png -query)
