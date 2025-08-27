set(MODULE concurrency)

# Collect test source files
file(GLOB_RECURSE DS_TEST_FILES CONFIGURE_DEPENDS *.cpp *.hpp)

# Build test executable
add_executable(${MODULE}_tests ${DS_TEST_FILES})

# Link with the library
target_link_libraries(${MODULE}_tests PRIVATE ${MODULE}_lib gtest)
