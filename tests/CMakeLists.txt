# Test executable for math_utils
add_executable(test_math_utils
  test_math_utils.cpp
)

target_include_directories(test_math_utils PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# Link against our static library and gtest
target_link_libraries(test_math_utils
  PRIVATE ${PROJECT_NAME}_lib
  PRIVATE GTest::gtest_main
)

# Add the test to CTest
include(GoogleTest)
gtest_discover_tests(test_math_utils)