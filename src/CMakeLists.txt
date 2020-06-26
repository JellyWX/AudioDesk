link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

include_directories(${JSONCPP_INCLUDE_DIRS})

add_executable(audiodesk main.cpp setup.cpp ini.cpp device_querier.cpp audiodesk.cpp setup_window.cpp main_window.cpp utils.cpp button_row.cpp button_row.hpp soundfx_api.cpp soundfx_api.hpp sound.cpp sound.hpp)

target_link_libraries(audiodesk ${GTKMM_LIBRARIES} cpr::cpr ${JSONCPP_LIBRARIES})
