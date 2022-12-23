add_library(net)

if(MSVC)
  file(GLOB_RECURSE net_SOURCE_FILES "Windows/*.cpp")
else()
  logfatal("Support for other platforms requires implementation")
endif()
target_sources(net PRIVATE ${net_SOURCE_FILES})
