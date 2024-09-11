cmake_minimum_required( VERSION 3.5 )

# Name of Game (If you change this change it everywhere in this file)
project( SealEngineGame )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )

add_subdirectory( glfw )

include_directories( glad/include )

# Windows Specific Stuff
if ( MSVC )
	set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

add_executable( SealEngineGame WIN32 main.cpp engine.cpp glad/src/glad.c )
target_link_libraries( SealEngineGame glfw )
