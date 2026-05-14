set(MODULE utiles)

file(GLOB_RECURSE UTILES_TEST_FILES CONFIGURE_DEPENDS *.cpp *.hpp)

add_executable(${MODULE}_tests ${UTILES_TEST_FILES})

target_link_libraries(${MODULE}_tests PRIVATE utiles_lib gtest)
