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

# Add Seal Engine Library
add_library(SealEngine)
# Include SFML Headers Publicly
target_include_directories(SealEngine PUBLIC ${SFML_SOURCE_DIR}/include)
# Enable C++17
target_compile_features(SealEngine PRIVATE
    cxx_std_17
)
# Link SFML
target_link_libraries(SealEngine PRIVATE
    sfml-graphics
)
# Include Seal Engine Headers Publicly
target_include_directories(SealEngine PUBLIC include)
# Add Seal Engine Sources
target_sources(SealEngine PRIVATE
    src/Engine.cpp
)
# Install Seal Engine
install(TARGETS SealEngine)
