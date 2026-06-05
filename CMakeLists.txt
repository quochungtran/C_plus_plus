cmake_minimum_required(VERSION 3.22)
project(CppLearning CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(COMPILE_WARNS_FLAGS /W4 /WX)
else()
    set(COMPILE_WARNS_FLAGS -Wall -Wextra -Wpedantic)
endif()

enable_testing()
include(CTest)

# googletest must be added before any module that links against it
add_subdirectory(lib/googletest)

add_subdirectory(data_structures)
add_subdirectory(utiles)

# Optional modules — only built when the source directory exists
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/competitve_programming")
    add_subdirectory(competitve_programming)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/flatbuffers")
    add_subdirectory(flatbuffers)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/fbcache")
    add_subdirectory(fbcache)
endif()
