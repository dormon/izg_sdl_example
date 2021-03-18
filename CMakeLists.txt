cmake_minimum_required(VERSION 3.19)

project(izg_sdl_example)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1 ) 

add_subdirectory(SDL2-2.0.14)

add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)

#make run
add_custom_target(run ./${PROJECT_NAME})


