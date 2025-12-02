cmake_minimum_required(VERSION 3.15...4.2)

project(Playlist-Skip-List VERSION 1.0
        DESCRIPTION "A "
        LANGUAGES CXX)

add_executable(main app/main.cpp src/skiplist.cpp)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)