
set (handlerDir ${CMAKE_CURRENT_SOURCE_DIR}/Handler)

add_library(Handler ${handlerDir}/Handler.c)
target_include_directories(Handler PUBLIC ${includeDir})
target_link_libraries(Handler PUBLIC ${DEPENDENCIES_LINK_LIBS})
