cmake_minimum_required(VERSION 3.1)

project(AudioDesk)

find_package(PkgConfig)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git)
FetchContent_MakeAvailable(cpr)

pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src)
