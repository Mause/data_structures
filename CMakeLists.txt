cmake_minimum_required(VERSION 2.8)
project(data_structures)

include_directories(lib/dict.c/src)
include_directories(src)

add_library(queue src/queue/queue.c)
add_library("set" "src/set/set.c")
add_library(ll src/ll/ll.c)
add_library(arrr src/arr/arr.c)

target_link_libraries(queue ll)
target_link_libraries("set" dict)

