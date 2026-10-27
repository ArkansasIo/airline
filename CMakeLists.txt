cmake_minimum_required(VERSION 3.20)
project(airport_control VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(airline_core
    src/booking_service.cpp
)

target_include_directories(airline_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(airline_core PUBLIC cxx_std_20)

if (MSVC)
    target_compile_options(airline_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(airline_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()

add_executable(booking_service_test
    tests/booking_service_test.cpp
)
target_link_libraries(booking_service_test PRIVATE airline_core)
add_test(NAME booking_service_test COMMAND booking_service_test)

option(BUILD_LEGACY_CONSOLE "Build the original console application" ON)

if (BUILD_LEGACY_CONSOLE)
    add_executable(airport_legacy
        "access navigation control.cpp"
    )
    target_compile_features(airport_legacy PRIVATE cxx_std_20)
    if (MSVC)
        target_compile_options(airport_legacy PRIVATE /W3)
    else()
        target_compile_options(airport_legacy PRIVATE -Wall -Wextra -Wno-deprecated-declarations)
    endif()
endif()
