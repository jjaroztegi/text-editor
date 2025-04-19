cmake_minimum_required(VERSION 3.22)

project(text_editor LANGUAGES CXX)

# Locate SDL3 packages
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

# Add source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Create target
add_executable(text_editor ${SOURCES})

# Set C++ standard to 20
target_compile_features(text_editor PRIVATE cxx_std_20)

# Link required libraries
target_link_libraries(text_editor PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL3::SDL3main>
    $<IF:$<TARGET_EXISTS:SDL3::SDL3>,SDL3::SDL3,SDL3::SDL3-static>
    $<IF:$<TARGET_EXISTS:SDL3_ttf::SDL3_ttf>,SDL3_ttf::SDL3_ttf,SDL3_ttf::SDL3_ttf-static>
)