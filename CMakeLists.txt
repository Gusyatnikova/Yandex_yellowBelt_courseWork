cmake_minimum_required(VERSION 3.15)
project(course_work)

set(CMAKE_CXX_STANDARD 20)

add_executable(course_work main.cpp token.h token.cpp condition_parser.h condition_parser.cpp condition_parser_test.cpp test_runner.h test_runner.cpp Date.cpp Date.h Database.cpp Database.h Node.cpp Node.h database_test.cpp)