log_info("Configuring unit_tests")
add_executable(unit_tests)
file(GLOB_RECURSE unit_tests_SOURCE_FILES "*.cpp")
target_sources(unit_tests PRIVATE ${unit_tests_SOURCE_FILES})
target_link_libraries(unit_tests PRIVATE global_options gtest gmock)

gtest_discover_tests(
  unit_tests
  # [EXTRA_ARGS arg1...]
  [WORKING_DIRECTORY
  $<TARGET_FILE_DIR:unit_tests>]
  # [TEST_PREFIX prefix  ] [TEST_SUFFIX suffix] [NO_PRETTY_TYPES]
  # [NO_PRETTY_VALUES] [PROPERTIES name1 value1...] [TEST_LIST var]
  # [DISCOVERY_TIMEOUT seconds]
)
