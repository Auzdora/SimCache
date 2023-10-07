cmake_minimum_required(VERSION 3.10)

include(GoogleTest)

file(GLOB_RECURSE LINUX_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*/*test.cpp")

# #####################################################################################################################
# MAKE TARGETS
# #####################################################################################################################

# #########################################
# "make check-tests"
# #########################################
add_custom_target(build-tests COMMAND ${CMAKE_CTEST_COMMAND} --show-only)
add_custom_target(check-tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

# #########################################
# "make XYZ_test"
# #########################################
foreach (test_source ${LINUX_TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(simcache_test_filename ${test_source} NAME)
    string(REPLACE ".cpp" "" simcache_test_name ${simcache_test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${simcache_test_name} EXCLUDE_FROM_ALL ${test_source})
    add_dependencies(build-tests ${simcache_test_name})

    gtest_discover_tests(${simcache_test_name}
            EXTRA_ARGS
            --gtest_color=auto
            --gtest_output=xml:${CMAKE_BINARY_DIR}/test/${simcache_test_name}.xml
            --gtest_catch_exceptions=0
            DISCOVERY_TIMEOUT 120
            PROPERTIES
            TIMEOUT 120
            )

    target_link_libraries(${simcache_test_name} simcache gtest gmock_main)

    # Set test target properties and dependencies.
    set_target_properties(${simcache_test_name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
            COMMAND ${simcache_test_name}
            )
endforeach ()