cmake_minimum_required(VERSION 3.18)
project(Toader VERSION 0.1)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.c")

#add_executable(${PROJECT_NAME} src/main.c)
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror -g>)

target_include_directories(${PROJECT_NAME} PRIVATE include)
#target_include_directories(${PROJECT_NAME} PRIVATE include/entities)
#target_include_directories(${PROJECT_NAME} PRIVATE include/behaviors)

target_include_directories(${PROJECT_NAME} PRIVATE src)
#target_include_directories(${PROJECT_NAME} PRIVATE src/entities)
#target_include_directories(${PROJECT_NAME} PRIVATE src/behaviors)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_mixer)
