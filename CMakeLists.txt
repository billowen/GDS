cmake_minimum_required (VERSION 3.0)

SET (CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_definitions(-std=c++11)

option(PRINT_LOG "Allow the lib to print log information or not." OFF)
option(BUILD_TEST "Whether to build the test exectable or not." OFF)

if (PRINT_LOG)
    add_definitions(-D_DEBUG_LOG)
else ()
endif()
    



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
    techfile.cpp techfile.h
    log.cpp log.h
)



target_include_directories(libGDS PUBLIC ${CMAKE_SOURCE_DIR})

if (BUILD_TEST)
    add_executable(testGDS main.cpp)
    target_link_libraries(testGDS libGDS)
else()
endif()






