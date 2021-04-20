project(game)

add_executable(${PROJECT_NAME} source/main.cpp)

if(WIN32)
    #set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ../core/source)
target_include_directories(${PROJECT_NAME} PUBLIC ${STEAMWORKS_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} core ${STEAMWORKS_LIBRARY_LIB})

configure_file(steam_appid.txt ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
configure_file(${STEAMWORKS_LIBRARY_DLL} ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
