function(set_default_compiler_options target)
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
      OR CMAKE_C_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
      # Support Unix Makefiles and Ninja
      set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    endif()
    target_compile_options(${target}
        PRIVATE -Werror
        PRIVATE -Wall
        PRIVATE -Wextra
        PRIVATE -Wunused
        PRIVATE -Wformat
        PRIVATE -Wmissing-include-dirs
        PRIVATE -Wno-pessimizing-move
#        PRIVATE -Wfloat-equal
        PRIVATE -Wswitch-default
        PRIVATE -Wdouble-promotion
#        PRIVATE -Wswitch-enum
        PRIVATE -Wpedantic
        PRIVATE -pedantic-errors)
  elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC" OR CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Not possible to set "/MT" or "/MTd" for Visual Studio 15 2017 generator via MSVC_RUNTIME_LIBRARY
    # https://gitlab.kitware.com/cmake/cmake/-/issues/18390
    # Override for now via add_compile_options
    target_compile_options(${target}
#        PRIVATE /Wall   # Enable all warnings
#        PRIVATE /WX     # Warning as error
        PRIVATE /EHsc
        PRIVATE "$<$<CONFIG:>:/MT>"
        PRIVATE "$<$<CONFIG:Debug>:/MTd>"
        PRIVATE "$<$<CONFIG:Release>:/MT>"
    )
  else()
    message(WARNING "No compiler options found for the detected compiler")
  endif()

endfunction()
