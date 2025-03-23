cmake_minimum_required(VERSION 3.22)
project(text_editor LANGUAGES CXX)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_TTF CONFIG REQUIRED)

add_executable(text_editor src/main.cpp)

target_compile_features(text_editor PRIVATE cxx_std_20)
target_link_libraries(text_editor PRIVATE SDL2::SDL2)
target_link_libraries(text_editor PRIVATE SDL2::SDL2main)
target_link_libraries(text_editor PRIVATE SDL2_ttf::SDL2_ttf)
