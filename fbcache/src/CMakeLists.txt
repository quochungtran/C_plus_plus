# Define a macro to create an executable from a given .cpp filename
# to build a src binary in bin folder
set(MODULE fbcache)

macro(SOURCE_BUILDER filename)

    get_filename_component(_target "${filename}" NAME_WE)
    set(${_target}_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/${filename}")

    # Define the executable
    add_executable(${_target} ${${_target}_SRCS})

    # Set output name of the executable
    set_target_properties(${_target} PROPERTIES OUTPUT_NAME ${_target})

    # Set compile flags conditionally
    if(WIN32)
        set_target_properties(${_target} PROPERTIES COMPILE_FLAGS "${COMPILE_WARNS_FLAGS}")
    else()
        set_target_properties(${_target} PROPERTIES COMPILE_FLAGS "-g ${COMPILE_WARNS_FLAGS}")
    endif()

    install(TARGETS ${_target} DESTINATION ${MODULE})

endmacro()
