find_package(Magnum REQUIRED GL Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

if(NOT SealEngineGame)
    set(SealEngineGame "SealEngineGame")
endif()

add_executable(${SealEngineGame} WIN32
    SealEngine.cpp
    vector2.cpp
    sprite2d.cpp
    shader.cpp
)
target_link_libraries(${SealEngineGame} PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::Shaders
)

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${SealEngineGame})
