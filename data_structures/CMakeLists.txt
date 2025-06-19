# List of source files for the data_structures_lib
set(MODULE data_structures)

SET(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/node.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stack.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stackUsingArray.hpp
)

# Define a static library target with the given sources
add_library(${MODULE}_lib STATIC ${SOURCES})

# Make headers from src/ accessible to anything linking this library
# for example they are able to be included in ./test 
target_include_directories(${MODULE}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add the src and test subdirectories to the build
# This tells CMake to process the CMakeLists.txt files inside `src/` and `test/`
# Each of those directories must contain their own CMakeLists.txt file
# It's a way to modularize project: keep src logic and tests separate and clean
add_subdirectory(src)
add_subdirectory(test)