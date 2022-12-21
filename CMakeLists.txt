cmake_minimum_required(VERSION 3.21)

project(
  NetSolutions
  VERSION 0.0.1
  LANGUAGES CXX)

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

if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/out/Windows)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/out/Windows)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/out/Windows)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
      ${ROOT_DIR}/out/Linux/${CMAKE_BUILD_TYPE}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
      ${ROOT_DIR}/out/Linux/${CMAKE_BUILD_TYPE}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      ${ROOT_DIR}/out/Linux/${CMAKE_BUILD_TYPE}/lib)
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

# ============================================================================
# Build
# ============================================================================

# ----------------------------------------------------------------------------
# divert option/features/definitions propagation library
# ----------------------------------------------------------------------------
log_info("Configuring global_options")
add_library(global_options INTERFACE)
target_compile_features(global_options INTERFACE cxx_std_20)
if(MSVC)
  target_compile_definitions(global_options INTERFACE NOMINMAX
                                                      WIN32_LEAN_AND_MEAN)
endif()
target_precompile_headers(
  global_options
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
  <vector>)
if(MSVC)
  target_precompile_headers(
    global_options INTERFACE
    # Windows Library
    <Windows.h> <timeapi.h>)
endif()

# uncomment this when ready to work on warnings

# set_project_warnings(global_options)

# ============================================================================
# Libs
# ============================================================================

add_subdirectory(lib)

# ============================================================================
# Apps
# ============================================================================

add_subdirectory(src)

# ============================================================================
# Tests
# ============================================================================

add_subdirectory(tests)

# ============================================================================
# Install: TODO
# ============================================================================
