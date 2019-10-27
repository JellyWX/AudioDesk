cmake_minimum_required(VERSION 3.1)

project(AudioDesk)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src)