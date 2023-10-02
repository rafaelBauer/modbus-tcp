set(SPDLOG_GIT_TAG_DEFAULT v1.12.0)

# To reset this, add this to your CMake file  --> SET(SPDLOG_DEFAULT_FLAGS OFF CACHE BOOL "Remove the default flags from MULTI Team from SPDLOG")
option(SPDLOG_DEFAULT_FLAGS "Use MULTI team default flags for SPDLOG" ON)

if("${SPDLOG_GIT_TAG}" STREQUAL "")
  set(SPDLOG_GIT_TAG ${SPDLOG_GIT_TAG_DEFAULT})
endif()

if(NOT TARGET spdlog)
  FetchContent_Declare(
      spdlog
      GIT_REPOSITORY https://github.com/gabime/spdlog.git
      GIT_TAG ${SPDLOG_GIT_TAG}
  )
  FetchContent_GetProperties(spdlog)
  if(NOT spdlog_POPULATED)
    if(SPDLOG_DEFAULT_FLAGS)
      if(MSVC)
        add_compile_options(/EHsc)
        # Not possible to set "/MT" or "/MTd" for Visual Studio 15 2017 generator via MSVC_RUNTIME_LIBRARY
        # https://gitlab.kitware.com/cmake/cmake/-/issues/18390
        # Override for now via add_compile_options
        add_compile_options(
            $<$<CONFIG:>:/MT>
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
        )
      endif(MSVC)
      set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "Force STATIC library build in spdlog add_subdirectory")
      set(SPDLOG_NO_EXCEPTIONS ON CACHE BOOL "Force SPDLOG_NO_EXCEPTIONS in spdlog library in spdlog add_subdirectory")
    endif()
    FetchContent_Populate(spdlog)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
  endif()
endif()
