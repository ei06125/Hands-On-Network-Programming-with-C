add_executable(chapter02)
file(GLOB chapter02_SOURCE_FILES "*.cpp")
target_sources(chapter02 PRIVATE ${chapter02_SOURCE_FILES})
target_include_directories(chapter02 PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(chapter02 PRIVATE networkingTS)

if(OS_NAME_RESULT STREQUAL "Windows")
  file(GLOB_RECURSE chapter02_WINDOWS_SOURCE_FILES "Windows/*.cpp")
  target_sources(chapter02 PRIVATE ${chapter02_WINDOWS_SOURCE_FILES})
  target_precompile_headers(
    chapter02
    PRIVATE
    # Windows API
    ${windows_api_library_pch}
    # C++ Standard Library
    ${cpp_standard_library_pch}
    # C Standard Library
    ${c_standard_library_pch}
  )
elseif(OS_NAME_RESULT STREQUAL "Linux")

  file(GLOB_RECURSE chapter02_LINUX_SOURCE_FILES "Linux/*.cpp")
  target_sources(chapter02 PRIVATE ${chapter02_LINUX_SOURCE_FILES})
  target_precompile_headers(
    chapter02
    PRIVATE
    # Linux API
    ${linux_api_library_pch}
    # C++ Standard Library
    ${cpp_standard_library_pch}
    # C Standard Library
    ${c_standard_library_pch}
  )
else()
  # TODO
endif()
