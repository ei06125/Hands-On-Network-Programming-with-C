add_executable(chapter01)
file(GLOB_RECURSE chapter01_SOURCE_FILES "*.cpp")
target_sources(chapter01 PRIVATE ${chapter01_SOURCE_FILES})
target_link_libraries(chapter01 PRIVATE networkingTS)

if(OS_NAME_RESULT STREQUAL "Windows")
  target_precompile_headers(
    chapter01
    PRIVATE
    # Windows API
    ${windows_api_library_pch}
    # C++ Standard Library
    ${cpp_standard_library_pch}
    # C Standard Library
    ${c_standard_library_pch}
  )
elseif(OS_NAME_RESULT STREQUAL "Linux")
  target_precompile_headers(
    chapter01
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
