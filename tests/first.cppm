module;
#include <gtest/gtest.h>

export module Tests;

export namespace Tests {
  TEST(ExampleTest, Basic) {
    EXPECT_EQ(2 + 2, 4);
  }
}