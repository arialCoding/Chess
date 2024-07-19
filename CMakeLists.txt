cmake_minimum_required(VERSION 3.20)

project(chess)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set (sourceDir ${CMAKE_CURRENT_SOURCE_DIR}/source)
set (includeDir ${sourceDir}/include)
set (DEPENDENCIES_LINK_LIBS SDL2::SDL2 SDL2_image)
set (LOCAL_LINK_LIBS Handler)

add_subdirectory(${sourceDir})


add_executable(Chess ${sourceDir}/main.c)
target_include_directories(Chess PUBLIC ${includeDir})
target_link_libraries(Chess PUBLIC ${DEPENDENCIES_LINK_LIBS} ${LOCAL_LINK_LIBS})
