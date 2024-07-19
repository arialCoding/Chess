
add_library(Handler ${sourceDir}/Handler.c)
target_include_directories(Handler PUBLIC ${includeDir})
target_link_libraries(Handler PUBLIC ${DEPENDENCIES_LINK_LIBS})


add_library(App ${sourceDir}/App.c)
target_include_directories(App PUBLIC ${includeDir})    
target_link_libraries(App PUBLIC ${DEPENDENCIES_LINK_LIBS} Handler)
