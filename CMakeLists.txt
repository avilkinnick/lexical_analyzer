cmake_minimum_required(VERSION 3.10)

project(lexical_analyzer LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(TARGET_NAME lexical_analyzer)

add_executable(${TARGET_NAME}
    ${PROJECT_SOURCE_DIR}/main.c
)

if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W3)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
