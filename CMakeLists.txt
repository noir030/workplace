cmake_minimum_required(VERSION 3.10)

project(Workplace)

set(CMAKE_CXX_STANDARD 17)

add_executable(workplace src/main.cpp src/csv_reader.cpp)

target_include_directories(workplace PUBLIC ${PROJECT_SOURCE_DIR}/include)