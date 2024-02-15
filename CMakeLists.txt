cmake_minimum_required(VERSION 3.26)
project(lablatory_13 C)

set(CMAKE_C_STANDARD 11)

add_executable(lablatory_13 main.c
        libs/algorithms/array/array.c
        libs/algorithms/array/array.h
        libs/algorithms/algorithms.h
        libs/algorithms/algorithms.c
        libs/data_structure/bitset/bitset.c
        libs/data_structure/bitset/bitset.h
        libs/algorithms/unordered_array/unordered_array_set.c
        libs/algorithms/unordered_array/unordered_array_set.h
        libs/algorithms/ordered_array/ordered_array_set.c
        libs/algorithms/ordered_array/ordered_array_set.h
        libs/algorithms/gfunc/gfunc.c
        libs/algorithms/testing/testing.c)