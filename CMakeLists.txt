cmake_minimum_required(VERSION 3.19)

project(C2PluginLoader)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE src/main.cpp)

add_library(${PROJECT_NAME} MODULE ${SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/" OUTPUT_NAME "XAPOFX1_5" SUFFIX ".dll")
