add_library(
        simcache_server
        OBJECT
        server.cpp
        router.cpp
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:simcache_server>
        PARENT_SCOPE)