cmake_minimum_required(VERSION 3.5) 
project(APP_RUN LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
    /usr/local/include/
    # ./threadpool
)

# aux_source_directory(./threadpool ThreadPool)
aux_source_directory(. main)

# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME}
    ${main}
    # ${ThreadPool}
) 
target_link_libraries(${PROJECT_NAME}
    pthread
    ) 