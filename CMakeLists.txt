cmake_minimum_required(VERSION 3.13)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(modbus-tcp)
include(FetchContent)
# Append custom cmake modules path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/module)

include(clang-format)
include(clang-tidy)
include(sanitizer)
include(compiler-options)
include(print-target-properties)

# Set our project to use C++ 17
set(CMAKE_CXX_STANDARD 17)

# Available options for smart bo
option(MODBUS_TCP_CLANG_TIDY "Enable Clang-tidy for Modbus-TCP" OFF)
option(MODBUS_TCP_BUILD_TESTS "Build Modbus-TCP tests" ON)

add_subdirectory(thirdparty)

# Source folders
add_subdirectory(src)
add_subdirectory(example)

create_clang_format_targets()
# Status messages
message(STATUS "======================== Modbus TCP Options ================================")
message(STATUS "MODBUS_TCP_CLANG_TIDY is set to ${MODBUS_TCP_CLANG_TIDY}")
message(STATUS "MODBUS_TCP_BUILD_TESTS is set to ${MODBUS_TCP_BUILD_TESTS}")
message(STATUS "====================== End of Modbus TCP Options ===========================")

message(STATUS "======================== Toolchain Settings ===============================")
message(STATUS "CMAKE_VERSION is set to ${CMAKE_VERSION}")
message(STATUS "CMAKE_BUILD_TYPE is set to ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_TOOLCHAIN_FILE is set to ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_C_COMPILER_ID: ${CMAKE_C_COMPILER_ID}")
message(STATUS "CMAKE_C_COMPILER_VERSION: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_MAKE_PROGRAM: ${CMAKE_MAKE_PROGRAM}")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
print_clang_tidy_version()
print_clang_format_version()
message(STATUS "==================== End of Toolchain Settings ============================")
