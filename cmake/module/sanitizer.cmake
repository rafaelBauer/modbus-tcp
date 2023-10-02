include_guard(GLOBAL)

## https://clang.llvm.org/docs/
SET(CMAKE_GLOBAL_NOSANITIZERECOVER_LIST
        # 'stops' execution on the first hit of broken code with a 'runtime error: division by zero'
        undefined
        float-divide-by-zero
        null
        address
        enum
        )

# finding a meaningful default
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(SANITIZE_DEFAULT ON)
elseif(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    set(SANITIZE_DEFAULT OFF)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Apple-Clang")
    set(SANITIZE_DEFAULT ON)
else()
    set(SANITIZE_DEFAULT OFF)
endif()

# the SANITIZE_DEFAULT can still be overridden by -DSANITIZE=ON/OFF by the user invoking cmake
option(SANITIZE "Force sanitize checks" ${SANITIZE_DEFAULT})

macro(target_add_default_sanitize TARGET_NAME)
    if(SANITIZE)
        message(STATUS "${TARGET_NAME}: Applying fsanitize/fno-sanitize-recover flags")
#        foreach(EL IN LISTS CMAKE_GLOBAL_SANITIZE_LIST)
#            target_link_options(${TARGET_NAME} PRIVATE "-fsanitize=${EL}")
#            target_compile_options(${TARGET_NAME} PRIVATE "-fsanitize=${EL}")
#        endforeach()
        foreach(EL IN LISTS CMAKE_GLOBAL_NOSANITIZERECOVER_LIST)
            target_link_options(${TARGET_NAME} PRIVATE "-fno-sanitize-recover=${EL}")
            target_compile_options(${TARGET_NAME} PRIVATE "-fno-sanitize-recover=${EL}")
        endforeach()
    endif()
endmacro()
