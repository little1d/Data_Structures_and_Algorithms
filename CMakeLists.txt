cmake_minimum_required(VERSION 3.26)
project(Data_Structures_and_Algorithms C)

set(CMAKE_C_STANDARD 11)

add_executable(Data_Structures_and_Algorithms
        Bank_calling_system/main.c
        Bank_calling_system/user_table_generate.c
        Bank_calling_system/business_table.h)
