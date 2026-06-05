set(MODULE data_structures)

# Builds a standalone executable from a single .cpp entry point
macro(SOURCE_BUILDER filename)
    get_filename_component(_target "${filename}" NAME_WE)
    add_executable(${_target} ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
    target_link_libraries(${_target} PRIVATE ${MODULE}_lib)
    target_include_directories(${_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(${_target} PRIVATE
        ${COMPILE_WARNS_FLAGS}
        $<$<CONFIG:Debug>:-g>
    )
    install(TARGETS ${_target} DESTINATION ${MODULE})
endmacro()

SOURCE_BUILDER(main.cpp)
