cmake_minimum_required(VERSION 3.16)
project(super-fs-browser C)

set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(
    /usr/local/include
    )

link_directories(
    /usr/local/lib
    )

set(CURSES_NEED_NCURSES "TRUE")
set(CURSES_NEED_WIDE "TRUE")

find_package(Curses)

if (!Curses_FOUND)
    add_definitions("-DNOCURSES")
endif()


find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(super-fs-browser main.c client.c client.h server.c server.h utils.c utils.h ui.c ui.h flist.c flist.h slist.c slist.h)

target_link_libraries(super-fs-browser ${CURSES_LIBRARIES} Threads::Threads)
