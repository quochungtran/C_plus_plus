set(MODULE data_structures)

# List test files explicitly — CMake docs recommend against GLOB for sources
set(DS_TEST_FILES
    array_test.cpp
    vector_test.cpp
    node_test.cpp
    list_test.cpp
    sharedPointer_test.cpp
    scoped_thread_test.cpp
    stack_test.cpp
    threadSafe_queue_test.cpp
    threadSafe_stack_test.cpp
    threadSafe_lookupTable_test.cpp
    threadSafe_list_test.cpp
)

add_executable(${MODULE}_tests ${DS_TEST_FILES})

# gtest_main provides main() that calls RUN_ALL_TESTS() — no custom main needed
target_link_libraries(${MODULE}_tests PRIVATE ${MODULE}_lib gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(${MODULE}_tests)
