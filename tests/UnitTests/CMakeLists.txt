log_info("Configuring net_unit_tests")

add_executable(net_unit_tests)
file(GLOB_RECURSE unit_tests_SOURCE_FILES "*.cpp")
target_sources(net_unit_tests PRIVATE ${unit_tests_SOURCE_FILES})
target_link_libraries(net_unit_tests PRIVATE net gtest gmock)
target_include_directories(net_unit_tests PRIVATE ${ROOT_DIR}/include)

gtest_discover_tests(net_unit_tests)

log_info("Configuring net_unit_tests -- DONE")
