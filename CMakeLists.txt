cmake_minimum_required(VERSION 3.20)
project(LabQueue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Queue STATIC src/queue.cpp)
target_include_directories(Queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(QueueApp app/main.cpp)
target_link_libraries(QueueApp PRIVATE Queue)

include(CTest)
if(BUILD_TESTING)
    add_executable(QueueTests tests/test_queue.cpp)
    target_link_libraries(QueueTests PRIVATE Queue)
    add_test(NAME QueueTests COMMAND QueueTests)
endif()
