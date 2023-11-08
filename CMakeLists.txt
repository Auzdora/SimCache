cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For clang-tidy.
set(BUILD_SHARED_LIBS OFF) # We expect external libraries to be linked statically.
set(CMAKE_CXX_STANDARD 17) # Compile as C++17.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Require C++17 support.

project(SimCache
        VERSION 2023.9
        DESCRIPTION "The SimChache is a simple distributed cache system, for now only implement server side"
        LANGUAGES C CXX
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        message(STATUS "Setting build type to `Debug` as none was specified.")
        set(CMAKE_BUILD_TYPE "Debug")
endif()

# Check if Google Test exists in the third_party directory
set(GTEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest")
file(GLOB GTEST_CONTENTS "${GTEST_ROOT}/*")
if(NOT EXISTS "${GTEST_ROOT}" OR GTEST_CONTENTS STREQUAL "")
  # Clone Google Test into third_party directory if it doesn't exist
  execute_process(
    COMMAND git clone https://github.com/google/googletest.git ${GTEST_ROOT}
  )
endif()

# Check if cpp-httplib exists in the third_party directory
set(HTTPLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp_httplib")
file(GLOB HTTPLIB_CONTENTS "${HTTPLIB_ROOT}/*")
if(NOT EXISTS "${HTTPLIB_ROOT}" OR HTTPLIB_CONTENTS STREQUAL "")
  # Clone Google Test into third_party directory if it doesn't exist
  execute_process(
    COMMAND git clone https://github.com/yhirose/cpp-httplib.git ${HTTPLIB_ROOT}
  )
endif()

# Check if nlohmann json exists in the third_party directory
set(JSON_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/json")
file(GLOB JSON_CONTENTS "${JSON_ROOT}/*")
if(NOT EXISTS "${JSON_ROOT}" OR JSON_CONTENTS STREQUAL "")
  # Clone Google Test into third_party directory if it doesn't exist
  execute_process(
    COMMAND git clone https://github.com/nlohmann/json.git ${JSON_ROOT}
  )
endif()

# Check if nlohmann json exists in the third_party directory
set(RPC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/rpc")
file(GLOB RPC_CONTENTS "${RPC_ROOT}/*")
if(NOT EXISTS "${RPC_ROOT}" OR RPC_CONTENTS STREQUAL "")
  # Clone Google Test into third_party directory if it doesn't exist
  execute_process(
    COMMAND git clone https://github.com/qicosmos/rest_rpc ${RPC_ROOT}
  )
endif()

find_package(Boost)

# #####################################################################################################################
# COMPILER SETUP
# #####################################################################################################################

message("Build mode: ${CMAKE_BUILD_TYPE}")

# Compiler flags.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter -Wno-attributes -Wno-unused-variable -Wno-missing-field-initializers -Wno-reorder")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -fno-omit-frame-pointer -fno-optimize-sibling-calls")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

# Output directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Includes.
set(LINUX_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
set(LINUX_TEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test/include)
set(LINUX_THIRD_PARTY_INCLUDE_DIR
        ${PROJECT_SOURCE_DIR}/third_party
)

include_directories(${LINUX_SRC_INCLUDE_DIR} ${LINUX_TEST_INCLUDE_DIR} ${LINUX_THIRD_PARTY_INCLUDE_DIR})
include_directories(BEFORE src) # This is needed for gtest.

function(disable_target_warnings NAME)
        target_compile_options(${NAME} PRIVATE "-w")
endfunction()

# #####################################################################################################################
# Other CMake modules
# MUST BE ADDED AFTER CONFIGURING COMPILER PARAMETERS
# #####################################################################################################################

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(apps)