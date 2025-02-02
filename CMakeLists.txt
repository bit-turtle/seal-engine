cmake_minimum_required(VERSION 3.5)
project(SealEngine)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

# Add SDL2 as a subproject
set(SDL_STATIC ON CACHE BOOL "SDL as a Static Library" FORCE)
add_subdirectory( SDL )

# Add Corrade as a subproject
add_subdirectory(corrade EXCLUDE_FROM_ALL)

# Add Magnum as a subproject, enable Sdl2Application
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/SDL2-2.30.9 ${CMAKE_PREFIX_PATH})
set(MAGNUM_WITH_SDL2APPLICATION ON CACHE BOOL "Use SDL2 with Magnum" FORCE)
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
add_subdirectory(magnum EXCLUDE_FROM_ALL)

# Build Seal Engine
include_directories( include )
add_subdirectory(src)
