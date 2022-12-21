add_executable(fuzz_tests)
file(GLOB_RECURSE fuzz_tests_SOURCE_FILES "*.cpp")
target_sources(fuzz_tests PRIVATE ${fuzz_tests_SOURCE_FILES})