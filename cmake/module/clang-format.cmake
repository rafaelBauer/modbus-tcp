include_guard(GLOBAL)

if("${CLANG_FORMAT_BIN}" STREQUAL "" OR "${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
  find_program(CLANG_FORMAT_BIN clang-format-10 NAMES clang-format)
else()
  set(CLANG_FORMAT_BIN ${CLANG_FORMAT_BIN})
endif()

if("${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
  message(STATUS "Looking for Clang-format - not found")
else()
  message(STATUS "Looking for Clang-format - found: ${CLANG_FORMAT_BIN}")
endif()

# Create cache variables if they don't exist
if(NOT CLANG_FORMAT_FILES)
  set(CLANG_FORMAT_FILES "" CACHE INTERNAL "Files to be formatted")
endif()

if(NOT CLANG_FORMAT_TARGETS)
  set(CLANG_FORMAT_TARGETS "" CACHE INTERNAL "Targets being formatted") # Variable only used for printing which targets were formatted
endif()

# - Function to add target sources and headers to check-format and fix-format targets
# The creation of check-format and fix-format are not done by this function. To do so,
# please call create_clang_format_targets()
#
# The function will take all the sources and also headers within the directories added to the
# target_include_directories.
#
# Apart from that, one can also include additional paths, but those are optional.
#
#    target_clang_format_setup(<target> [<path1> <path2> ...])
function(target_clang_format_setup target)
  if("${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
    message(STATUS "No clang-format binary defined. So target ${target} not added to clang-format")
    return()
  endif()

  get_target_property(target_type ${target} TYPE)
  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    get_target_property(target_sources ${target} INTERFACE_SOURCES)
    get_target_property(target_include_dirs ${target} INTERFACE_INCLUDE_DIRECTORIES)
  else()
    get_target_property(target_sources ${target} SOURCES)
    get_target_property(target_include_dirs ${target} INCLUDE_DIRECTORIES)
  endif()
  # Update the cache variable with the targets
  set(targets ${CLANG_FORMAT_TARGETS})
  if(NOT "${target}" IN_LIST targets)
    list(APPEND targets ${target})
    set(CLANG_FORMAT_TARGETS ${targets} CACHE INTERNAL "Targets being formatted")
    # No need to return yet, since we have the line to remove duplicates from the files to format ahead.
  endif()

  # Initialize internal variable that holds the files that need to be formatted
  set(files_to_format ${CLANG_FORMAT_FILES})

  # Append files to clang-format from target sources
  if(NOT "${target_sources}" STREQUAL "target_sources-NOTFOUND")
    foreach(clang_format_source ${target_sources})
      get_filename_component(clang_format_source ${clang_format_source} ABSOLUTE)
      list(APPEND files_to_format ${clang_format_source})
    endforeach()
  endif()

  # Append files from include directories
  if(NOT "${target_include_dirs}" STREQUAL "target_include_dirs-NOTFOUND")
    foreach(clang_format_path ${target_include_dirs})
      file(GLOB_RECURSE current_path_sources
          ${clang_format_path}/*.h
          ${clang_format_path}/*.hpp
          ${clang_format_path}/*.cpp
          )
      foreach(clang_format_source ${current_path_sources})
        get_filename_component(clang_format_source ${clang_format_source} ABSOLUTE)
        list(APPEND files_to_format ${clang_format_source})
      endforeach()
    endforeach()
  endif()

  # Append files in extra paths given in optional argument
  foreach(clang_format_path ${ARGN})
    file(GLOB_RECURSE current_path_sources
        ${clang_format_path}/*.h
        ${clang_format_path}/*.hpp
        ${clang_format_path}/*.cpp
        )
    foreach(clang_format_source ${current_path_sources})
      get_filename_component(clang_format_source ${clang_format_source} ABSOLUTE)
      list(APPEND files_to_format ${clang_format_source})
    endforeach()
  endforeach()

  # Remove duplicates of the list, since some might be twice due to second loop
  list(REMOVE_DUPLICATES files_to_format)
  set(CLANG_FORMAT_FILES ${files_to_format} CACHE INTERNAL "Targets being formatted")
endfunction()

# - Function used to create the targets fix-format and check-format.
#
# Meant to be only called once per cmake run. Usually the top most project should call this
# function.
function(create_clang_format_targets)
  message(STATUS "===================== Targets to be formatted =============================")
  foreach(formatted_target ${CLANG_FORMAT_TARGETS})
    message(STATUS "   - ${formatted_target}")
  endforeach()
  message(STATUS "================== End of Targets to be formatted =========================")

  if(NOT TARGET fix-format)
    add_custom_target(fix-format
        COMMAND ${CLANG_FORMAT_BIN} -style=file -i ${CLANG_FORMAT_FILES}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Formatting the targets with ${CLANG_FORMAT_BIN}. To check which targets, look at the cmake generation output."
        )
  endif()

  if(NOT TARGET check-format)
    add_custom_target(check-format
        COMMAND ${CLANG_FORMAT_BIN} -style=file --dry-run --Werror ${CLANG_FORMAT_FILES}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Checking format of the targets with ${CLANG_FORMAT_BIN}. To check which targets, look at the cmake generation output."
        )
  endif()
endfunction()

function(print_clang_format_version)
  if(NOT "${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
    message(STATUS "CLANG_FORMAT_BIN: ${CLANG_FORMAT_BIN}")
    execute_process(COMMAND ${CLANG_FORMAT_BIN} --version
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE CLANG_TIDY_RESULT RESULT_VARIABLE ret)
    if(NOT ret EQUAL "0")
      message( FATAL_ERROR "execute_process '${CLANG_FORMAT_BIN} --version: returned error: ${ret}")
    endif()

    STRING(REGEX MATCH "version ([0-9]+\\.[0-9]+\\.[0-9]+)" CLANG_FORMAT_VERSION_LONG "${CLANG_TIDY_RESULT}")
    STRING(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" CLANG_FORMAT_VERSION "${CLANG_FORMAT_VERSION_LONG}")
    message(STATUS "CLANG_FORMAT_VERSION: ${CLANG_FORMAT_VERSION} ")
    message(STATUS "One can set the CLANG_FORMAT binary using: 'cmake -DCLANG_FORMAT_BIN=/usr/bin/clang-format-10 ..'")
  else()
    message(STATUS "Clang-format not found")
  endif()
endfunction()
