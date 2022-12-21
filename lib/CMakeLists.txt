add_library(net)
file(GLOB_RECURSE net_SOURCE_FILES "*.cpp")
target_sources(net PRIVATE ${net_SOURCE_FILES})
