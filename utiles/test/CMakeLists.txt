set(MODULE utiles)

set(UTILES_TEST_FILES
    main.cpp
)

add_executable(${MODULE}_tests ${UTILES_TEST_FILES})

target_link_libraries(${MODULE}_tests PRIVATE utiles_lib gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(${MODULE}_tests)
