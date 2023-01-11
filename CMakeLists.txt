# ##############################################################################
# Copyright (C) Studio Katakana. All Rights Reserved.
# ##############################################################################

# ##############################################################################
# Configuring
# ##############################################################################

# ==============================================================================
# CMake General Settings
# ==============================================================================

cmake_minimum_required(VERSION 3.16)

project(
  NetworkingTS
  VERSION 0.0.1
  LANGUAGES CXX
)

# ------------------------------------------------------------------------------
# CMake Include Modules
# ------------------------------------------------------------------------------

include(FetchContent)

# ------------------------------------------------------------------------------
# CMake Cache Variables & Options
# ------------------------------------------------------------------------------

# short alias for top-level root folder
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

# VRVIU is not using the latest standard
set(CMAKE_CXX_STANDARD 20)

# prevent std=gnu++20 or similar
set(CMAKE_CXX_EXTENSIONS OFF)

# Surpress CTest Targets (Continuous, Experimental, Nightly)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

# Surpresses MSVC Target ZERO_CHECK
set(CMAKE_SUPPRESS_REGENERATION ON)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_DEBUG_POSTFIX d)

# Check to see if this project is the root/top-level project
if(CMAKE_VERSION VERSION_LESS 3.21)
  # This variable is set by project() in CMake 3.21+
  string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}"
                 PROJECT_IS_TOP_LEVEL
  )
endif()

# ==============================================================================
# CMake Dependencies
# ==============================================================================

message("[INFO] Configuring CMake Dependencies")

# ------------------------------------------------------------------------------
# ei06125_cmake_modules
# ------------------------------------------------------------------------------

message("[INFO] Downloading ei06125_cmake_modules")

if(MSVC)
  set(EI06125_CMAKE_MODULES_GIT_REPOSITORY
      https://github.com/ei06125/ei06125_cmake_modules.git
  )
else()
  set(EI06125_CMAKE_MODULES_GIT_REPOSITORY
      git@github.com:ei06125/ei06125_cmake_modules.git
  )
endif()

FetchContent_Declare(
  ei06125_cmake_modules
  GIT_REPOSITORY ${EI06125_CMAKE_MODULES_GIT_REPOSITORY}
  GIT_TAG 573fb011e552d4e5245a8764d34396a89f8ba2f1 # v0.0.1
)

message("[INFO] Making ei06125_cmake_modules available")
FetchContent_MakeAvailable(ei06125_cmake_modules)
log_info("Downloading ei06125_cmake_modules -- done")
log_info("Configuring CMake Dependencies -- done")

# ##############################################################################
# Building
# ##############################################################################

# ==============================================================================
# Utilities
# ==============================================================================

find_program(CLANGTIDY clang-tidy)
if(CLANGTIDY)
  set(NET_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
else()
  log_error("clang-tidy requested but executable not found")
endif()

# ==============================================================================
# Dependencies
# ==============================================================================

log_info("Fetching spdlog...")
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36 # release-1.11.0
)
log_info("Fetching spdlog -- done")
log_info("Making spdlog available...")
FetchContent_MakeAvailable(spdlog)
log_info("Making spdlog available -- done")

# ==============================================================================
# Hands-On Networking Programming With C examples
# ==============================================================================

add_subdirectory(examples)

# ==============================================================================
# global settings that propagate options/definitions/features to linking targets
# ==============================================================================

add_library(net_global_settings INTERFACE)
set_project_warnings(net_global_settings)
if(OS_NAME_RESULT STREQUAL "Windows")
  target_compile_definitions(
    net_global_settings INTERFACE WIN32_LEAN_AND_MEAN NOMINMAX
                                  _WIN32_WINNT=0x0600
  )
endif()

set(c_standard_library_pch <cassert>)
set(cpp_standard_library_pch
    <deque>
    <list>
    <memory>
    <queue>
    <stdexcept>
    <string>
    <unordered_map>
    <unordered_set>
    <vector>
)
set(windows_api_library_pch <Windows.h> <WinSock2.h> <Ws2tcpip.h> <iphlpapi.h>)
set(linux_api_library_pch
    <arpa/inet.h>
    <errno.h>
    <fcntl.h>
    <ifaddrs.h>
    <netdb.h>
    <netinet/in.h>
    <sys/socket.h>
    <sys/types.h>
    <unistd.h>
)

# ==============================================================================
# net: Networking TS main library
# ==============================================================================

add_subdirectory(lib)

# ==============================================================================
# Hands-On Networking Programming With C++ examples
# ==============================================================================

add_subdirectory(src)

# ##############################################################################
# Testing
# ##############################################################################

option(NET_BUILD_TESTS "Build test targets" ${PROJECT_IS_TOP_LEVEL})
if(NET_BUILD_TESTS)

  # ----------------------------------------------------------------------------
  # Test Dependencies
  # ----------------------------------------------------------------------------
  enable_testing()
  include(CTest)
  log_info("Configuring Google Test")
  find_package(Threads REQUIRED)
  find_package(GTest)
  if(NOT GTest_FOUND)
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/_deps/googletest-src)
      log_warn("Configuring Google Test -- NOT FOUND")
      log_info("Downloading into ${CMAKE_BINARY_DIR}/_deps")
      FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
      )
      FetchContent_MakeAvailable(googletest)
    else()
      log_warn("Configuring Google Test -- FOUND in ${CMAKE_BINARY_DIR}/_deps")
      add_subdirectory(${CMAKE_BINARY_DIR}/_deps/googletest-src)
    endif()
    log_info("You might want to try installing on your system")
    add_library(EI06125::GTest ALIAS gtest)
    add_library(EI06125::GMock ALIAS gmock)
  else()
    add_library(EI06125::GTest ALIAS GTest::gtest)
    add_library(EI06125::GMock ALIAS GTest::gmock)
  endif(NOT GTest_FOUND)
  include(GoogleTest)
  log_info("Configuring Google Test -- done")

  # ----------------------------------------------------------------------------
  # Test Targets
  # ----------------------------------------------------------------------------

  add_subdirectory(tests)

endif(NET_BUILD_TESTS)

# ##############################################################################
# Installing
# ##############################################################################

# ##############################################################################
# Packaging
# ##############################################################################
