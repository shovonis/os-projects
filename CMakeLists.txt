cmake_minimum_required(VERSION 3.8)
project(project1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c assign1/source/assign1part1.c assign1/source/test.c assign1/source/assign1part2.c assign1/source/pagetable.h assign1/source/phypages.h assign1/source/pagetable.c assign1/source/phypages.c assign1/source/assign1part3.c)
add_executable(project1 ${SOURCE_FILES})