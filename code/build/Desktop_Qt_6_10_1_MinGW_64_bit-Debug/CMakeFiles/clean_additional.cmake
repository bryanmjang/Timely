# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "_deps\\googletest-build\\googlemock\\CMakeFiles\\gmock_autogen.dir\\AutogenUsed.txt"
  "_deps\\googletest-build\\googlemock\\CMakeFiles\\gmock_autogen.dir\\ParseCache.txt"
  "_deps\\googletest-build\\googlemock\\CMakeFiles\\gmock_main_autogen.dir\\AutogenUsed.txt"
  "_deps\\googletest-build\\googlemock\\CMakeFiles\\gmock_main_autogen.dir\\ParseCache.txt"
  "_deps\\googletest-build\\googlemock\\gmock_autogen"
  "_deps\\googletest-build\\googlemock\\gmock_main_autogen"
  "_deps\\googletest-build\\googletest\\CMakeFiles\\gtest_autogen.dir\\AutogenUsed.txt"
  "_deps\\googletest-build\\googletest\\CMakeFiles\\gtest_autogen.dir\\ParseCache.txt"
  "_deps\\googletest-build\\googletest\\CMakeFiles\\gtest_main_autogen.dir\\AutogenUsed.txt"
  "_deps\\googletest-build\\googletest\\CMakeFiles\\gtest_main_autogen.dir\\ParseCache.txt"
  "_deps\\googletest-build\\googletest\\gtest_autogen"
  "_deps\\googletest-build\\googletest\\gtest_main_autogen"
  "app\\CMakeFiles\\Timely_autogen.dir\\AutogenUsed.txt"
  "app\\CMakeFiles\\Timely_autogen.dir\\ParseCache.txt"
  "app\\Timely_autogen"
  "core\\CMakeFiles\\core_autogen.dir\\AutogenUsed.txt"
  "core\\CMakeFiles\\core_autogen.dir\\ParseCache.txt"
  "core\\core_autogen"
  "test\\unit_tests\\CMakeFiles\\unit_tests_autogen.dir\\AutogenUsed.txt"
  "test\\unit_tests\\CMakeFiles\\unit_tests_autogen.dir\\ParseCache.txt"
  "test\\unit_tests\\unit_tests_autogen"
  "ui\\CMakeFiles\\ui_autogen.dir\\AutogenUsed.txt"
  "ui\\CMakeFiles\\ui_autogen.dir\\ParseCache.txt"
  "ui\\ui_autogen"
  )
endif()
