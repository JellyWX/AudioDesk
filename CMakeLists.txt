set (CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.1)

project(AudioDesk)

find_package(PkgConfig)

include(FindFontconfig)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git)
FetchContent_MakeAvailable(cpr)

pkg_check_modules(GTKMM gtkmm-3.0)

include(FindJsoncpp.cmake)

add_subdirectory(src)
