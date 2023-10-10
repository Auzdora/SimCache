add_subdirectory(server)
add_subdirectory(store)

add_library(simcache STATIC ${ALL_OBJECT_FILES})

set(CACHE_LIBS
simcache_server
simcache_storage
        )

target_link_libraries(
        simcache
        ${CACHE_LIBS})

target_include_directories(
        simcache PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
