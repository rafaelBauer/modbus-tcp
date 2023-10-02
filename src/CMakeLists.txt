if(MODBUS_TCP_CLANG_TIDY)
  target_run_clang_tidy()
endif()


file(GLOB_RECURSE SOURCES ./*.cpp)

add_library(rh-device-manager STATIC ${SOURCES})
add_library(RH::Device::Manager ALIAS rh-device-manager)

set_default_compiler_options(rh-device-manager)

target_include_directories(rh-device-manager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                            PUBLIC  ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(rh-device-manager PRIVATE modbuspp
                                        PRIVATE spdlog::spdlog)

target_compile_definitions(rh-device-manager PRIVATE SPDLOG_ACTIVE_LEVEL=TRACE)

target_add_default_sanitize(rh-device-manager)
target_clang_format_setup(rh-device-manager)
print_target_properties(rh-device-manager)
