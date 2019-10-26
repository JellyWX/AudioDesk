cmake_minimum_required(VERSION 3.1)

project(Minesweeper)

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "minesweeper")
add_executable(${EXECUTABLE_NAME} main.cpp)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
if(SFML_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)