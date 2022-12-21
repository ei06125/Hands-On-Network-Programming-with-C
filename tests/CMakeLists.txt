set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

find_package(Threads REQUIRED)
include(CTest)
enable_testing()

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)


add_subdirectory(UnitTests)
add_subdirectory(PerfTests)
add_subdirectory(FuzzTests)
