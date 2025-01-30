# seal-engine CMakeLists.txt

cmake_minimum_required( VERSION 3.5 )

project( seal-engine )

include_directories( ${OPENGL_INCLUDE_DIRS} )

# GLFW
set( GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )
add_subdirectory( glfw )

# GLAD
include_directories( glad/include )

# Windows Specific Graphics Startup
if ( MSVC )
	set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

# Create Engine Executable
include_directories( include )
add_library( seal-engine src/engine.cpp glad/src/glad.c )
# Link GLFW (Window and I/O Manager)
target_link_libraries( seal-engine glfw )
