link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(audiodesk main.cpp setup.cpp ini.cpp device_querier.cpp audiodesk.cpp setup_window.cpp main_window.cpp utils.cpp button_row.cpp button_row.hpp)

target_link_libraries(audiodesk ${GTKMM_LIBRARIES})