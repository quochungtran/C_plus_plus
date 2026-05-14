# Source files for utiles_lib (no headers, no entry points with main())
set(UTILES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UP_Time.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logging.cpp
)

add_library(utiles_lib STATIC ${UTILES_SOURCES})

# Make headers from src/ accessible to anything linking this library
target_include_directories(utiles_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(test)
