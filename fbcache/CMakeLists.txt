# List of source files for the data_structures_lib
get_filename_component(MODULE ${CMAKE_CURRENT_SOURCE_DIR} NAME)
SET(_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CacheBuilder.cpp
)

# Define a static library target with the given sources
add_library(${MODULE}_lib STATIC ${_SOURCES})

# Make headers from src/ accessible to anything linking this library
# for example they are able to be included in ./test 
target_include_directories(${MODULE}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# add flatbuffers lib in module
target_link_libraries(${MODULE}_lib PRIVATE flatbuffers)

# Add the src and test subdirectories to the build
# This tells CMake to process the CMakeLists.txt files inside `src/` and `test/`
# Each of those directories must contain their own CMakeLists.txt file
# It's a way to modularize project: keep src logic and tests separate and clean
add_subdirectory(src)
add_subdirectory(test)