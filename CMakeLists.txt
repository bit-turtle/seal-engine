cmake_minimum_required(VERSION 3.12)
project(SealEngine LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Get SFML
option(BUILD_SHARED_LIBS "SFML Static Library" OFF)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Default Seal Engine Game Name
if(NOT SealEngineGame)
    set(SealEngineGame "SealEngineGame")
endif()
# Add Seal Engine Executable
add_executable(${SealEngineGame})
# Enable C++17
target_compile_features(${SealEngineGame} PRIVATE
    cxx_std_17
)
# Link SFML
target_link_libraries(${SealEngineGame} PRIVATE
    sfml-graphics
)
# Include Seal Engine Headers
include_directories(include)
# Add Seal Engine Sources
target_sources(${SealEngineGame} PRIVATE
    src/Engine.cpp
)
# Install Seal Engine Game
install(TARGETS ${SealEngineGame})
