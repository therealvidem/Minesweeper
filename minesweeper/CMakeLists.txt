find_package(raylib 3.5 REQUIRED)

add_library(
    minesweeper
    board.c
    minesweeper.c
    point.c
    point_queue.c
)

target_include_directories(minesweeper PUBLIC ${RAYLIB_INCLUDE_DIR})
target_link_libraries(minesweeper ${RAYLIB_LIBRARIES})