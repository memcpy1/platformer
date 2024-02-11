cmake_minimum_required(VERSION 3.5)
project(gameEngine2D VERSION 0.0.1 LANGUAGES CXX)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED true)

add_library(${PROJECT_NAME} source/engine.cpp)
target_include_directories( ${PROJECT_NAME} 
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
)

target_link_libraries( ${PROJECT_NAME}
    PUBLIC
    PRIVATE
)