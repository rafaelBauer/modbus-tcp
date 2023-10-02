function(print_target_properties TARGET_NAME)
    message(STATUS "-------------- ${TARGET_NAME} Target ------------------------")

    get_target_property(CURRENT_COMPILE_OPTIONS ${TARGET_NAME} COMPILE_OPTIONS)
    message(STATUS "    COMPILE_OPTIONS: ${CURRENT_COMPILE_OPTIONS}")
    message(STATUS "-------------- End of ${TARGET_NAME} Target ------------------------")
endfunction()
