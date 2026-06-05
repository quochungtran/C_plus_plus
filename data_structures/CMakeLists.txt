set(MODULE data_structures)

# All data structures are header-only templates — use INTERFACE library
add_library(${MODULE}_lib INTERFACE)

# Expose src/ so that test/ and any executable can #include headers directly
target_include_directories(${MODULE}_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(test)
