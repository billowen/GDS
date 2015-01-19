cmake_minimum_required (VERSION 3.0)

SET (CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_definitions(-std=c++11)


project (GDS)
add_library (libGDS aref.cpp
				aref.h
                    boundary.cpp
                    elements.cpp
                    exceptions.cpp
                    gdsio.cpp
                    library.cpp
                    path.cpp
                    sref.cpp
                    structures.cpp
                    text.cpp
                    tags.h
                    )

target_include_directories(libGDS PUBLIC ${CMAKE_SOURCE_DIR})






