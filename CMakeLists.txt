cmake_minimum_required(VERSION 3.0.0)
project(
    minesweeper_game
    VERSION 0.1.0
)

find_package(raylib 3.5 REQUIRED)

set(CMAKE_C_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/minesweeper)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(minesweeper_game ${SRC_FILES})

target_include_directories(
    minesweeper_game PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/minesweeper/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics
)

target_link_libraries(minesweeper_game minesweeper)

target_include_directories(minesweeper_game PUBLIC ${RAYLIB_INCLUDE_DIR})
target_link_libraries(minesweeper_game ${RAYLIB_LIBRARIES})

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
