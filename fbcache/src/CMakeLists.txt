# Get the module name from the parent of the current directory (e.g., 'fbcache')
get_filename_component(MODULE_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(MODULE ${MODULE_DIR} NAME)
string(TOLOWER ${MODULE} MODULE_LOWER)

# Define a macro to build an executable from a single .cpp file
macro(SOURCE_BUILDER filename)
    get_filename_component(_target "${filename}" NAME_WE)
    set(${_target}_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/${filename}")

    add_executable(${_target} ${${_target}_SRCS})

    set_target_properties(${_target} PROPERTIES OUTPUT_NAME ${_target})

    if(WIN32)
        set_target_properties(${_target} PROPERTIES COMPILE_FLAGS "${COMPILE_WARNS_FLAGS}")
    else()
        set_target_properties(${_target} PROPERTIES COMPILE_FLAGS "-g ${COMPILE_WARNS_FLAGS}")
    endif()

    # Install the binary to bin/<module>/
    install(TARGETS ${_target} DESTINATION "bin/${MODULE_LOWER}")
endmacro()
