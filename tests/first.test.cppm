module;

#include <gtest/gtest.h>

export module FirstTest;

export namespace FirstTest {
  TEST(ExampleTest, Basic) {
    EXPECT_EQ(2 + 2, 4);
  }
}