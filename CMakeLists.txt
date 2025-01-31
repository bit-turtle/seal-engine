# seal-engine CMakeLists.txt

cmake_minimum_required( VERSION 3.5..3.10 )

project( seal-engine )

include_directories( ${OPENGL_INCLUDE_DIRS} )

# GLFW
set( GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )
add_subdirectory( glfw )

# Magnum
set( CORRADE_BUILD_STATIC ON CACHE BOOL "Corrade as a Static Library" FORCE )
add_subdirectory( corrade EXCLUDE_FROM_ALL )
set( MAGNUM_BUILD_STATIC ON CACHE BOOL "Magnum as a Static Library" FORCE )
set( MAGNUM_WITH_ANYIMAGEIMPORTER ON CACHE BOOL "Magnum AnyImageImporter" FORCE )
set( MAGNUM_WITH_ANYSCENEIMPORTER ON CACHE BOOL "Magnum AnySceneImporter" FORCE )
set( MAGNUM_WITH_GL ON CACHE BOOL "Magnum OpenGL" FORCE )
set( MAGNUM_WITH_SHADERS ON CACHE BOOL "Magnum Shaders" FORCE )
if ( APPLE )
	set( MAGNUM_WITH_CGLCONTEXT ON CACHE BOOL "CGL OpenGL Context on Mac" FORCE )
elseif( UNIX )
	set( MAGNUM_WITH_GLXCONTEXT ON CACHE BOOL "GLX OpenGL Context on Linux" FORCE )
elseif( WIN32 )
	set( MAGNUM_WITH_WGL ON CACHE BOOL "WGL OpenGL Context on Windows" FORCE )
else()
	message( FATAL_ERROR "No OpenGL Context Handler Available on this platform!" )
endif()
add_subdirectory( magnum EXCLUDE_FROM_ALL )

# Create Seal Engine Library
include_directories( include )
# Build Seal Engine Library
add_library( seal-engine )
add_subdirectory( src )
# Link GLFW (Window and I/O Manager)
target_link_libraries( seal-engine PRIVATE glfw )
# Link Magnum (Graphics Library)
target_link_libraries( seal-engine PRIVATE
	Corrade::Main
	Magnum::GL
	GLContext
	Magnum::Magnum
	Magnum::Shaders
)
