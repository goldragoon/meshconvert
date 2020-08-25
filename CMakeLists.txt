# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("meshconvert")
find_package(assimp REQUIRED)
find_package(cxxopts REQUIRED)
find_package(Boost COMPONENTS filesystem)

add_executable(meshconvert "src/main.cpp" "src/util.h")

target_link_libraries(meshconvert PRIVATE assimp)
target_link_libraries(meshconvert PRIVATE cxxopts::cxxopts)
target_link_libraries(meshconvert PRIVATE ${Boost_LIBRARIES})
