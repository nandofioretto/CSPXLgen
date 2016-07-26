# read: http://www.cmake.org/Wiki/CMake/Tutorials/How_to_create_a_ProjectConfig.cmake_file

cmake_minimum_required(VERSION 3.3)
project(CSPXLgen)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(VERSION  ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

set(SOURCE_DIR src/)
set(LIB_DIR lib/)
set(BIN_DIR bin/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/ffiorett/Repositories/CSPXLgen/bin")

include_directories(
        "${SOURCE_DIR}"
        "${LIB_DIR}/misc_utils"
)


set(SOURCE_FILES main.cpp
        src/LargeGraph.hpp
        src/LargeInstance.cpp
        src/LargeInstance.hpp
        src/Constraint.hpp
        src/Input.hpp
        src/Output.cpp
        src/Output.hpp src/InstanceFactory.hpp)
add_executable(CSPXLgen ${SOURCE_FILES})