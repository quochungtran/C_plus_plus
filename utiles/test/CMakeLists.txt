# Collect test source files
file(GLOB_RECURSE DS_TEST_FILES CONFIGURE_DEPENDS *.cpp *.hpp)

# Build test executable
add_executable(utiles_tests ${DS_TEST_FILES})

# Link with the library
target_link_libraries(utiles_tests PRIVATE data_structures_lib gtest)
