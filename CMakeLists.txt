cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include)
add_library(SealEngine
    # Seal Engine Source Files
    src/Engine.cpp
)
# Link SFML
target_compile_features(SealEngine PRIVATE cxx_std_17)
target_link_libraries(SealEngine PRIVATE
   SFML::System
   SFML::Graphics
)
