cmake_minimum_required(VERSION 3.20)

project(chess)

if(WIN32)
    set (SDL2_dir ${CMAKE_SOURCE_DIR}/vendor/SDL2)
    link_directories(${SDL2_dir}/lib)
    set (includeDir ${SDL2_dir}/include)
else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
endif()

set (sourceDir ${CMAKE_CURRENT_SOURCE_DIR}/source)
set (includeDir ${includeDir} ${sourceDir}/include)
set (DEPENDENCIES_LINK_LIBS SDL2main SDL2 SDL2_image)
set (LOCAL_LINK_LIBS Handler App)


add_library(Handler ${sourceDir}/Handler.c)
target_include_directories(Handler PUBLIC ${includeDir})
target_link_libraries(Handler PUBLIC ${DEPENDENCIES_LINK_LIBS})

set (AppSources ${sourceDir}/App.c
                ${sourceDir}/Game.c)

add_library(App ${AppSources})
target_include_directories(App PUBLIC ${includeDir})    
target_link_libraries(App PUBLIC ${DEPENDENCIES_LINK_LIBS} Handler)


add_executable(Chess ${sourceDir}/main.c)
target_include_directories(Chess PUBLIC ${includeDir})
target_link_libraries(Chess PUBLIC ${DEPENDENCIES_LINK_LIBS} ${LOCAL_LINK_LIBS})

set (resources_dir ${sourceDir}/resource)
set (destination_dir ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_custom_command(
    TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${resources_dir} ${destination_dir}/resource
    COMMENT "Copying resources"
)
