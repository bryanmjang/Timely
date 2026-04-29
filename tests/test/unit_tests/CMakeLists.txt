cmake_minimum_required(VERSION 3.16)

include(FetchContent)

# Download GoogleTest/GoogleMock at configure time
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# On Windows this prevents overriding parent CRT settings (mostly MSVC-related, safe to keep)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
  tst_event_manager.cpp
  tst_validate.cpp
)

target_link_libraries(unit_tests PRIVATE
  GTest::gtest_main
  GTest::gmock
  core
  Qt::Core
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
