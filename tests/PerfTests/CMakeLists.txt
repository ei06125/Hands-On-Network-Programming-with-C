add_executable(perf_tests)
file(GLOB_RECURSE perf_tests_SOURCE_FILES "*.cpp")
target_sources(perf_tests PRIVATE ${perf_tests_SOURCE_FILES})
