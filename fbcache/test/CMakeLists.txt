# Get the module name (parent directory of 'test/')
get_filename_component(MODULE_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(MODULE_NAME ${MODULE_DIR} NAME)

# Set dynamic names
set(TEST_TARGET "${MODULE_NAME}_tests")
set(LIB_TARGET "${MODULE_NAME}_lib")

# Collect test source files
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS *.cpp *.hpp)

# Build test executable with dynamic name
add_executable(${TEST_TARGET} ${TEST_FILES})

# Link with the dynamically named library and gtest
target_link_libraries(${TEST_TARGET} PRIVATE ${LIB_TARGET} gtest)
