project(editor)

add_executable(${PROJECT_NAME} source/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ../core/source)

target_link_libraries(${PROJECT_NAME} core)
