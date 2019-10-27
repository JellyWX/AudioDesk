link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(audiodesk main.cpp)

target_link_libraries(audiodesk ${GTKMM_LIBRARIES})