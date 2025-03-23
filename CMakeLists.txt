cmake_minimum_required(VERSION 3.22)

project(text_editor LANGUAGES CXX)

# Locate SDL2 packages
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_TTF CONFIG REQUIRED)

# Create target
add_executable(text_editor src/main.cpp)

# Set C++ standard to 20
target_compile_features(text_editor PRIVATE cxx_std_20)

# Link required libraries
target_link_libraries(text_editor PRIVATE 
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
)