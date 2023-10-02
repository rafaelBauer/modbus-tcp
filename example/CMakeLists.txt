if(MODBUS_TCP_CLANG_TIDY)
  target_run_clang_tidy()
endif()

set(SOURCES main.cpp MainMenu.cpp Menu.cpp)

add_executable(rh-device-manager-cli ${SOURCES})

set_default_compiler_options(rh-device-manager-cli)

target_include_directories(rh-device-manager-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rh-device-manager-cli
    PRIVATE RH::Device::Manager
    PRIVATE spdlog::spdlog)

target_compile_definitions(rh-device-manager PRIVATE SPDLOG_ACTIVE_LEVEL=TRACE)

target_add_default_sanitize(rh-device-manager-cli)
target_clang_format_setup(rh-device-manager-cli)
print_target_properties(rh-device-manager-cli)
