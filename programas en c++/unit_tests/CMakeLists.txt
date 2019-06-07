cmake_minimum_required(VERSION 3.10.2)

include(ExternalProject)
ExternalProject_Add(googletest
    SOURCE_DIR      googletest-src
    BINARY_DIR      googletest-build
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         master
    INSTALL_COMMAND "")

# Locate GTest
#find_package(gtest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories("${gtest_SOURCE_DIR}/include"
    "${gmock_SOURCE_DIR}/include")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(executeTests sqrt_test.cpp)
target_link_libraries(executeTests ${GTEST_LIBRARIES} pthread)


get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
