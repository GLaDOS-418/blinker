cmake_minimum_required(VERSION ${CMAKE_VERSION})

find_package(Catch2 CONFIG REQUIRED)

add_executable( ${PROJECT_NAME}-tests )

target_link_libraries( ${PROJECT_NAME}-tests
  PRIVATE
    Catch2::Catch2WithMain
    ${PROJECT_NAME}-lib
 )

target_sources( ${PROJECT_NAME}-tests
  PRIVATE
    catch_main.cpp
    tests.cpp
  )

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}-tests)
