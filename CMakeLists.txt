cmake_minimum_required (VERSION 3.0)

SET (CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_definitions(-std=c++11)


project (GDS)
add_library (libGDS
	aref.cpp
	aref.h
    boundary.cpp
	boundary.h				
    elements.cpp
	elements.h
	exceptions.cpp
	exceptions.h
	gdsio.cpp
	gdsio.h
    library.cpp
	library.h
    path.cpp
	path.h
    sref.cpp
	sref.h
    structures.cpp
	structures.h
    text.cpp
	text.h
    tags.h
	gadgets.cpp gadgets.h
)

target_include_directories(libGDS PUBLIC ${CMAKE_SOURCE_DIR})

add_subdirectory(test)






