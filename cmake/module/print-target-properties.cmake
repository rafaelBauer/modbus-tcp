function(print_target_properties TARGET_NAME)
    message(STATUS "-------------- ${TARGET_NAME} Target ------------------------")

    get_target_property(CURRENT_COMPILE_OPTIONS ${TARGET_NAME} COMPILE_OPTIONS)
    get_target_property(CURRENT_LINK_OPTIONS ${TARGET_NAME} LINK_OPTIONS)
    message(STATUS "    COMPILE_OPTIONS: ${CURRENT_COMPILE_OPTIONS}")
    message(STATUS "    LINK_OPTIONS: ${CURRENT_LINK_OPTIONS}")
    message(STATUS "-------------- End of ${TARGET_NAME} Target ------------------------")
endfunction()
