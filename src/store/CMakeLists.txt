add_library(
        simcache_storage
        OBJECT
        storage_engine.cpp
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:simcache_storage>
        PARENT_SCOPE)