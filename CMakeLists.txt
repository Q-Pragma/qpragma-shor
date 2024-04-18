# ####################### #
# Configure cmake project #
# ####################### #

# Define project
project(qpragma-shor LANGUAGES CXX)
cmake_minimum_required(VERSION 3.10.2)

# Define useful variables
include("cmake/environ.cmake")


# ######################## #
# Q-Pragma shor executable #
# ######################## #

# Define C++ files
include_directories(${INCLUDE_DIR})

set(qpragma-shor-cpp
        ${SRC_DIR}/fraction.cpp
        ${SRC_DIR}/continued_fraction.cpp
        ${SRC_DIR}/display.cpp)

set(qpragma-shor-headers
        ${INCLUDE_DIR}/qpragma/shor.h
        ${INCLUDE_DIR}/qpragma/shor/fraction.h
        ${INCLUDE_DIR}/qpragma/shor/continued_fraction.h
        ${INCLUDE_DIR}/qpragma/shor/core.h
        ${INCLUDE_DIR}/qpragma/shor/core.ipp
        ${INCLUDE_DIR}/qpragma/shor/display.h)

# Define compilation rules
add_executable(qpragma-shor ${qpragma-shor-cpp} ${SRC_DIR}/main.cpp)
target_link_libraries(qpragma-shor qpragma qpragma-pybindlinalg qatnewlinalg boost_program_options)
set_target_properties(
    qpragma-shor PROPERTIES PUBLIC_HEADER "${qpragma-shor-headers}"
                            LINKER_LANGUAGE CXX
                            COMPILE_FLAGS -fplugin=qpragma-plugin.so)

# Install
install(TARGETS qpragma-shor
        RUNTIME DESTINATION usr/bin)


# ############# #
# Project tests #
# ############# #

# Define C++ test files
set(tests-shor-cpp
        ${TESTS_DIR}/tests_main.cpp
        ${TESTS_DIR}/tests_continued_fraction.cpp)

# Define executatable
add_executable(qpragma-shor-tests EXCLUDE_FROM_ALL ${qpragma-shor-cpp} ${tests-shor-cpp})
target_link_libraries(qpragma-shor-tests gtest)
set_target_properties(qpragma-shor-tests PROPERTIES PRIVATE_HEADER "${qpragma-shor-headers}")

# Define targets
add_custom_target(cpp_tests
    DEPENDS qpragma-shor-tests
    COMMAND $<TARGET_FILE:qpragma-shor-tests>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(check DEPENDS cpp_tests)
