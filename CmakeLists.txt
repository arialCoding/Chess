cmake_minimum_required(VERSION 3.20)

project(chess)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

set (sourceDir ${CMAKE_CURRENT_SOURCE_DIR}/source)


add_executable(Chess ${sourceDir}/main.c)
target_include_directories(Chess PUBLIC ${sourceDir}/include)
target_link_libraries(Chess PUBLIC ${SDL_LINK_LIBS})
