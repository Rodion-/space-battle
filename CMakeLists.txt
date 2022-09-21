cmake_minimum_required(VERSION 3.15.3)


set (PROJECT_NAME space_battle)
project(${PROJECT_NAME} CXX )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(targetName ${PROJECT_NAME})

IF (NOT DEFINED TEST_RUN)
    SET(TEST_RUN 0 )
ENDIF() 

ADD_DEFINITIONS(-DTEST_RUN=${TEST_RUN})

set(coreSources   main.cpp )


add_executable(${targetName} ${coreSources} )

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

target_compile_options(${targetName} PRIVATE
                        -Wall
                        -g

                      )


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
