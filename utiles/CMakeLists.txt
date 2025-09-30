# List of source files for the data_structures_lib
SET(DS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UP_Time.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/processMearsure.cpp
)

# Define a static library target with the given sources
add_library(utiles_lib STATIC ${DS_SOURCES})

# Make headers from src/ accessible to anything linking this library
# for example they are able to be included in ./test 
target_include_directories(utiles_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add the src and test subdirectories to the build
# This tells CMake to process the CMakeLists.txt files inside `src/` and `test/`
# Each of those directories must contain their own CMakeLists.txt file
# It's a way to modularize project: keep src logic and tests separate and clean
add_subdirectory(src)
