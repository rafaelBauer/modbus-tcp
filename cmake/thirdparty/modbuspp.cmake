set(MODBUSPP_GIT_TAG_DEFAULT patch-1)

if("${MODBUSPP_GIT_TAG}" STREQUAL "")
  set(MODBUSPP_GIT_TAG ${MODBUSPP_GIT_TAG_DEFAULT})
endif()

# To reset this, add this to your CMake file  --> SET(MODBUSPP_DEFAULT_FLAGS OFF CACHE BOOL "Remove the default flags from MULTI Team from modbuspp")
option(MODBUSPP_DEFAULT_FLAGS "Use MULTI team default flags for modbuspp" ON)

if(NOT TARGET modbuspp)
  FetchContent_Declare(
      modbuspp
      GIT_REPOSITORY https://github.com/rafaelBauer/modbuspp.git
      GIT_TAG ${MODBUSPP_GIT_TAG}
  )
  FetchContent_GetProperties(modbuspp)
  if(NOT modbuspp_POPULATED)
    if(MODBUSPP_DEFAULT_FLAGS)
      # Nothing to add here yet
    endif()
    FetchContent_Populate(modbuspp)
    add_subdirectory(${modbuspp_SOURCE_DIR} ${modbuspp_BINARY_DIR})
  endif()
endif()
