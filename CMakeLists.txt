cmake_minimum_required( VERSION 3.5 )

# Name of Game (If you change this change it everywhere in this file)
project( SealEngineGame )

include_directories( ${OPENGL_INCLUDE_DIRS} )

# GLFW
set( GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )
add_subdirectory( glfw )

# GLAD
include_directories( glad/include )

# React Physics 3D
add_subdirectory( reactphysics3d )

# Windows Specific Stuff
if ( MSVC )
	set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

# Create Game Executable
add_executable( SealEngineGame WIN32 main.cpp engine.cpp glad/src/glad.c )
# Link GLFW (Window and I/O Manager) and React Physics 3D (3D Physics Engine)
target_link_libraries( SealEngineGame glfw reactphysics3d )
