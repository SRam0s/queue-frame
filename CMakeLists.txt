cmake_minimum_required(VERSION 3.5) 
project(APP_RUN LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
    /usr/local/include/
)

aux_source_directory(. main)

add_executable(${PROJECT_NAME}
    ${main}
) 
target_link_libraries(${PROJECT_NAME}
    pthread
    ) 