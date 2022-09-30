cmake_minimum_required(VERSION 3.15.3)


set (PROJECT_NAME space_battle)
project(${PROJECT_NAME} CXX )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -pthread")

set(targetName ${PROJECT_NAME})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

IF (NOT DEFINED G_TEST_RUN)
    SET(G_TEST_RUN 0 )
ENDIF()

SET(G_TEST_RUN 1 )

ADD_DEFINITIONS(-DG_TEST_RUN=${G_TEST_RUN})

set(coreSources   main.cpp )

add_executable(${targetName} ${coreSources} )

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${GTEST_INCLUDE_DIRS}
                           )

target_link_libraries(${targetName} PUBLIC ${GTEST_BOTH_LIBRARIES}  )

target_compile_options(${targetName} PRIVATE
                        -Wall
                        -g

                      )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
