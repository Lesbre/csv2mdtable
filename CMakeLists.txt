cmake_minimum_required (VERSION 3.13)
project (CSV_to_MD_table)
# The version number.
set (VERSION_MAJOR 1)
set (VERSION_MINOR 1)

set (EXECUTABLE csv2mdtable)

set (CMAKE_CXX_STANDARD 20)

# set (DEBUG ON)
set (USE_ANSI ON)
set (POSIX ON)
# AUX_SOURCE_DIRECTORY(dir ./src)
set(SOURCE_FILES
	src/main.cpp
	src/io.cpp
	src/options.cpp
	src/parser.cpp
	src/formatter.cpp
)

# Compiler flags
if ( CMAKE_COMPILER_IS_GNUCC )
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Ofast")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=undefined -fsanitize-undefined-trap-on-error")
	set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")
endif()
if ( MSVC )
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/src/project.hpp.hpp"
	"${PROJECT_SOURCE_DIR}/src/project.hpp"
)

FIND_PACKAGE(Threads REQUIRED)

# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}")

# add the executable
add_executable(${EXECUTABLE} ${SOURCE_FILES})
