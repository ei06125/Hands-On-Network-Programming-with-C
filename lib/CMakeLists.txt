add_library(networkingTS)
file(GLOB networkingTS_SOURCE_FILES "*.cpp")
target_sources(networkingTS PRIVATE ${networkingTS_SOURCE_FILES})
target_include_directories(networkingTS PUBLIC ${ROOT_DIR}/include)
target_link_libraries(networkingTS PUBLIC net_global_settings spdlog)

if(OS_NAME_RESULT STREQUAL "Windows")

  file(GLOB_RECURSE networkingTS_WINDOWS_SOURCE_FILES "Windows/*.cpp")
  target_sources(networkingTS PRIVATE ${networkingTS_WINDOWS_SOURCE_FILES})
  target_precompile_headers(
    networkingTS
    PRIVATE
    # Windows API
    ${windows_api_library_pch}
    # C++ Standard Library
    ${cpp_standard_library_pch}
    # C Standard Library
    ${c_standard_library_pch}
  )

  target_link_libraries(networkingTS PUBLIC ws2_32 iphlpapi)

elseif(OS_NAME_RESULT STREQUAL "Linux")

  file(GLOB_RECURSE networkingTS_LINUX_SOURCE_FILES "Linux/*.cpp")
  target_sources(networkingTS PRIVATE ${networkingTS_LINUX_SOURCE_FILES})
  target_precompile_headers(
    networkingTS
    PRIVATE
    # Linux API
    ${linux_api_library_pch}
    # C++ Standard Library
    ${cpp_standard_library_pch}
    # C Standard Library
    ${c_standard_library_pch}
  )

else()

  file(GLOB_RECURSE networkingTS_MACOS_SOURCE_FILES "MacOS/*.cpp")
  target_sources(networkingTS PRIVATE ${networkingTS_MACOS_SOURCE_FILES})

endif()
