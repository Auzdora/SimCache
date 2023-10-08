find_package(Threads REQUIRED)
set(ENTRY_POINT_SOURCES main.cpp)
add_executable(server ${ENTRY_POINT_SOURCES})


target_link_libraries(server PRIVATE Threads::Threads simcache)
set_target_properties(server PROPERTIES OUTPUT_NAME simcache-server)