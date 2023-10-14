add_library(
        simcache_cache
        OBJECT
        cache_manager.cpp
        single_cache_manager.cpp
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:simcache_cache>
        PARENT_SCOPE)