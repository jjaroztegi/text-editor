cmake_minimum_required(VERSION 3.22)

project(text_editor LANGUAGES CXX)

# Locate SDL2 packages
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

# Add source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Create target
add_executable(text_editor ${SOURCES})

# Set C++ standard to 20
target_compile_features(text_editor PRIVATE cxx_std_20)

# Link required libraries
target_link_libraries(text_editor PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)