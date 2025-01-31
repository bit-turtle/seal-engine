# seal-engine src CMakeLists.txt

cmake_minimum_required( VERSION 3.5..3.10 )

# Add all cpp files as sources for seal-engine
file( GLOB SealEngineSourceFiles *.cpp )
target_sources( seal-engine PRIVATE ${SealEngineSourceFiles} )
