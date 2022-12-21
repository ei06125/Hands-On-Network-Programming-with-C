cmake_minimum_required(VERSION 3.21)

project(
  
  VERSION 0.0.4
  LANGUAGES CXX
)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
# set(CMAKE_CURRENT_LOG_LEVEL 2)
include(${ROOT_DIR}/tools/cmake/Modules/BuildToolsMain.cmake)

# Surpress CTest Targets (Continuous, Experimental, Nightly)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

if(NOT WIN32)
  message(FATAL_ERROR "This project only runs on Windows")
endif()

# Surpresses MSVC Target ZERO_CHECK
set(CMAKE_SUPPRESS_REGENERATION ON)
set(INSTALL_GTEST OFF)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_DEBUG_POSTFIX d)
set(CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(windivert_EXTERNAL_DIR ${ROOT_DIR}/external/WinDivert)
set(windivert_INCLUDE_DIRS ${windivert_EXTERNAL_DIR}/include)
find_file(windivert_LIBRARY WinDivert.lib HINTS "${windivert_EXTERNAL_DIR}/x64")

if(${windivert_LIBRARY} STREQUAL windivert_LIBRARY-NOTFOUND)
  message(FATAL_ERROR "windivert_LIBRARY is required")
endif()

if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/out/Windows)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/out/Windows)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/out/Windows)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
      ${ROOT_DIR}/out/Linux/${CMAKE_BUILD_TYPE}/bin
  )
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
      ${ROOT_DIR}/out/Linux/${CMAKE_BUILD_TYPE}/lib
  )
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      ${ROOT_DIR}/out/Linux/${CMAKE_BUILD_TYPE}/lib
  )
endif()

# ============================================================================
# Dependencies
# ============================================================================

include(FetchContent)

# ----------------------------------------------------------------------------
# spdlog
# ----------------------------------------------------------------------------

log_info("Configuring dependencies: spdlog")
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36 # release-1.11.0
)
FetchContent_MakeAvailable(spdlog)

log_info("Configuring dependencies: rapidjson")
FetchContent_Declare(
  rapidjson
  GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
  GIT_TAG f54b0e47a08782a6131cc3d60f94d038fa6e0a51 # release-1.1.0
)
FetchContent_GetProperties(rapidjson)
if(NOT rapidjson_POPULATED)
  FetchContent_Populate(rapidjson)
  set(RAPIDJSON_BUILD_DOC
      OFF
      CACHE STRING "Do NOT build rapidjson docs" FORCE
  )
  set(RAPIDJSON_BUILD_EXAMPLES
      OFF
      CACHE STRING "Do NOT build rapidjson examples" FORCE
  )
  set(RAPIDJSON_BUILD_TESTS
      OFF
      CACHE STRING "Do NOT build rapidjson tests" FORCE
  )
  set(rapidjson_INCLUDE_DIR ${rapidjson_SOURCE_DIR}/include)
  FetchContent_MakeAvailable(rapidjson)
endif()

log_info("Configuring dependencies: cxxopts")
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG 32afbc65263e42fa089f473d5a6131983d9b7200 # master (2022/12/16)
)
FetchContent_MakeAvailable(cxxopts)

# ============================================================================
# Build
# ============================================================================

# ----------------------------------------------------------------------------
# divert option/features/definitions propagation library
# ----------------------------------------------------------------------------
log_info("Configuring divert_options")
add_library(divert_options INTERFACE)
target_compile_features(divert_options INTERFACE cxx_std_20)
if(MSVC)
  target_compile_definitions(
    divert_options INTERFACE NOMINMAX WIN32_LEAN_AND_MEAN
  )
endif()
target_precompile_headers(
  divert_options
  INTERFACE
  # C Standard Library
  <cstdint>
  <cstdlib>
  # C++ Standard Library
  <algorithm>
  <exception>
  <filesystem>
  <iostream>
  <string>
  <string_view>
  <vector>
)
if(MSVC)
  target_precompile_headers(
    divert_options INTERFACE
    # Windows Library
    <Windows.h> <timeapi.h>
  )
endif()

# uncomment this when ready to work on warnings

# set_project_warnings(divert_options)

# ----------------------------------------------------------------------------
# divert library
# ----------------------------------------------------------------------------
log_info("Configuring divert")
add_library(divert)
file(GLOB_RECURSE divert_SOURCE_FILES "${ROOT_DIR}/lib/*.cpp")
target_sources(divert PRIVATE ${divert_SOURCE_FILES})
target_include_directories(
  divert PUBLIC ${ROOT_DIR}/lib ${windivert_INCLUDE_DIRS}
                ${rapidjson_INCLUDE_DIR}
)
target_link_libraries(divert PUBLIC divert_options spdlog)
if(MSVC)
  target_link_libraries(divert PUBLIC "Winmm" "ws2_32")
endif()

# ----------------------------------------------------------------------------
# divert CLI client
# ----------------------------------------------------------------------------
log_info("Configuring divert client")
add_executable(divert_cli)
file(GLOB_RECURSE divert_SOURCE_FILES "src/CLI/*.cpp")
file(GLOB_RECURSE divert_HEADER_FILES "src/CLI/*.h")
target_sources(divert_cli PRIVATE ${divert_SOURCE_FILES})
target_link_libraries(
  divert_cli
  PRIVATE divert
          # Dependencies
          ${windivert_LIBRARY} cxxopts
)
target_link_options(divert_cli PRIVATE "/SAFESEH:NO")
target_include_directories(divert_cli PRIVATE ${ROOT_DIR}/src/CLI)
get_filename_component(windivert_LIBRARY_DIR ${windivert_LIBRARY} DIRECTORY)
add_custom_command(
  TARGET divert_cli
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "Deleting old WinDivert.lib"
  COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE_DIR:divert_cli>/WinDivert.lib
  COMMAND ${CMAKE_COMMAND} -E echo "Copying new WinDivert.lib"
  COMMAND ${CMAKE_COMMAND} -E copy ${windivert_LIBRARY_DIR}/WinDivert.lib
          $<TARGET_FILE_DIR:divert_cli>
  COMMAND ${CMAKE_COMMAND} -E echo "Deleting old WinDivert.dll"
  COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE_DIR:divert_cli>/WinDivert.dll
  COMMAND ${CMAKE_COMMAND} -E echo "Copying new WinDivert.dll"
  COMMAND ${CMAKE_COMMAND} -E copy ${windivert_LIBRARY_DIR}/WinDivert.dll
          $<TARGET_FILE_DIR:divert_cli>
  COMMAND ${CMAKE_COMMAND} -E echo "Deleting old WinDivert64.sys"
  COMMAND ${CMAKE_COMMAND} -E remove
          $<TARGET_FILE_DIR:divert_cli>/WinDivert64.sys
  COMMAND ${CMAKE_COMMAND} -E echo "Copying new WinDivert64.sys"
  COMMAND ${CMAKE_COMMAND} -E copy ${windivert_LIBRARY_DIR}/WinDivert64.sys
          $<TARGET_FILE_DIR:divert_cli>
)

# ============================================================================
# Test
# ============================================================================

add_subdirectory(tests)

# ============================================================================
# Install
# ============================================================================

set(divert_INSTALL_DIR ${ROOT_DIR}/deploy)
if(MSVC)
  set(CMAKE_INSTALL_PREFIX ${divert_INSTALL_DIR}/Windows)
else()
  message(FATAL_ERROR "This project only runs on Windows")
endif()

install(TARGETS divert unit_tests DESTINATION bin)
install(FILES ${divert_HEADER_FILES} DESTINATION include)
install(FILES ${windivert_INCLUDE_DIRS}/windivert.h DESTINATION include)
install(FILES ${windivert_LIBRARY_DIR}/WinDivert.lib
              ${windivert_LIBRARY_DIR}/WinDivert.dll
              ${windivert_LIBRARY_DIR}/WinDivert64.sys DESTINATION bin
)
