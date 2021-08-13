cmake_minimum_required(VERSION 3.0.0)
project(
    minesweeper_game
    VERSION 0.1.0
)

find_package(raylib 3.5 QUIET)

# From https://github.com/raysan5/raylib/blob/master/projects/CMake/CMakeLists.txt
# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT RAYLIB_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib"
        GIT_TAG 3.5.0
    )

    FetchContent_GetProperties(raylib)
    if (NOT RAYLIB_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

        # build raylib
        add_subdirectory(${RAYLIB_SOURCE_DIR} ${RAYLIB_BINARY_DIR})

    endif()

endif()

set(CMAKE_C_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/minesweeper)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(minesweeper_game ${SRC_FILES})

if (MSCV)
    target_compile_options(minesweeper_game PUBLIC $<$<CONFIG:Debug>:/W4 /WX>)
else()
    target_compile_options(minesweeper_game PUBLIC $<$<CONFIG:Debug>:-Wall -Werror -Wextra -Wpedantic>)
endif()

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

# https://stackoverflow.com/questions/49636737/cmake-set-default-resource-asset-directory
set (source "${CMAKE_SOURCE_DIR}/assets")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "symbolic link assets folder from ${source} => ${destination}"
)
