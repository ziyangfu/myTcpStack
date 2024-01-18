cmake_minimum_required(VERSION 3.16)
project(myTcpStack
        LANGUAGES C
        VERSION 0.0.1
)
set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/tcpStack/include)
file(GLOB_RECURSE LIB_TCP_STACK_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/tcpStack/src/*.c)
file(GLOB_RECURSE LIB_TCP_STACK_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/tcpStack/include/*.h)
add_library(myTcpStack STATIC ${LIB_TCP_STACK_SRCS} ${LIB_TCP_STACK_HEADERS})
