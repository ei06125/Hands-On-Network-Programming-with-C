add_executable(chapter01)
file(GLOB chapter01_SOURCE_FILES "*.cpp")
target_sources(chapter01 PRIVATE ${chapter01_SOURCE_FILES})
target_include_directories(chapter01 PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(chapter01 PRIVATE networkingTS)

if(OS_NAME_RESULT STREQUAL "Windows")
  file(GLOB_RECURSE chapter01_WINDOWS_SOURCE_FILES "Windows/*.cpp")
  target_sources(chapter01 PRIVATE ${chapter01_WINDOWS_SOURCE_FILES})
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

  file(GLOB_RECURSE chapter01_LINUX_SOURCE_FILES "Linux/*.cpp")
  target_sources(chapter01 PRIVATE ${chapter01_LINUX_SOURCE_FILES})
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
