# Macro to build a standalone CLI executable from a single .cpp file
macro(SOURCE_BUILDER filename)

    get_filename_component(_target "${filename}" NAME_WE)

    add_executable(${_target} ${CMAKE_CURRENT_SOURCE_DIR}/${filename})

    target_link_libraries(${_target} PRIVATE utiles_lib)

    target_include_directories(${_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    target_compile_options(${_target} PRIVATE
        ${COMPILE_WARNS_FLAGS}
        $<$<CONFIG:Debug>:-g>
    )

    install(TARGETS ${_target} DESTINATION "utiles")

endmacro()

SOURCE_BUILDER(processMeasure_cli.cpp)
SOURCE_BUILDER(std_thread_cli.cpp)
