cmake_minimum_required (VERSION 3.5)
project (picrosssat LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MiniSat 2.2 REQUIRED)
find_package(GTest REQUIRED)

add_executable(picrosssat main.cpp io.cpp sat.cpp)
target_link_libraries(picrosssat MiniSat::libminisat)

add_executable(test test.cpp io.cpp sat.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

