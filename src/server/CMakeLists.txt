add_executable(server)
file(GLOB_RECURSE server_SOURCE_FILES "*.cpp")
target_sources(server PRIVATE ${server_SOURCE_FILES})