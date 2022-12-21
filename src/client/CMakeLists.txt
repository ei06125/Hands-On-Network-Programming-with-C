add_executable(client)
file(GLOB_RECURSE client_SOURCE_FILES "*.cpp")
target_sources(client PRIVATE ${client_SOURCE_FILES})