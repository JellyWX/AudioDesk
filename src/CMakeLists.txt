link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(audiodesk main.cpp setup.cpp ini.cpp device_querier.cpp audiodesk.cpp setup_window.cpp)

target_link_libraries(audiodesk ${GTKMM_LIBRARIES})