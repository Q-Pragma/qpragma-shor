# Define project
project(qpragma-shor LANGUAGES CXX)
cmake_minimum_required(VERSION 3.10.2)

# Define useful variables
include("cmake/environ.cmake")

# Define C++ files
include_directories(${INCLUDE_DIR})

set(qpragma-shor-cpp
        ${SRC_DIR}/fraction.cpp
        ${SRC_DIR}/continued_fraction.cpp
        ${SRC_DIR}/display.cpp
        ${SRC_DIR}/main.cpp)

set(qpragma-shor-headers
        ${INCLUDE_DIR}/qpragma/shor.h
        ${INCLUDE_DIR}/qpragma/shor/fraction.h
        ${INCLUDE_DIR}/qpragma/shor/continued_fraction.h
        ${INCLUDE_DIR}/qpragma/shor/display.h)

# Define compilation rules
add_executable(qpragma-shor ${qpragma-shor-cpp})
set_target_properties(
    qpragma-shor PROPERTIES PUBLIC_HEADER "${qpragma-shor-headers}"
                            LINKER_LANGUAGE CXX)

# Install
install(TARGETS qpragma-shor
        RUNTIME DESTINATION usr/bin)
