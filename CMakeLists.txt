cmake_minimum_required(VERSION 3.15)
project(course_work)

set(CMAKE_CXX_STANDARD 20)

add_executable(course_work main.cpp Token/token.h Token/token.cpp "Condition Parser/condition_parser.h" "Condition Parser/condition_parser.cpp" "Unit Test/condition_parser_test.cpp" "Unit Test/test_runner.h" "Unit Test/test_runner.cpp" Date/date.cpp Date/date.h Database/database.cpp Database/database.h Node/node.h "Unit Test/database_test.cpp" Node/Empty/empty_node.h "Node/Date Comparison/date_comparasion_node.h" "Node/Event Comparison/event_comparison_node.h" "Node/Logical Operation/logical_operaion_node.h" Node/Empty/empty_node.cpp "Node/Date Comparison/date_comparison_node.cpp" "Node/Event Comparison/event_comparison_node.cpp" "Node/Logical Operation/logical_operation_node.cpp")