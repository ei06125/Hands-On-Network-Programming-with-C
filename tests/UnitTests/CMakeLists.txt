add_executable(unit_tests)
file(GLOB_RECURSE unit_tests_SOURCE_FILES "*.cpp")
target_sources(unit_tests PRIVATE ${unit_tests_SOURCE_FILES})