module;

#include <gtest/gtest.h>

export module config.test;

import config;

export namespace ConfigTest {
  TEST(ConfigTest, Constructor) {
    EXPECT_NO_THROW(Config config);
  }

  TEST(ConfigTest, WebFields) {
    Config config = {};

    EXPECT_NO_THROW(config.web.port = 123;);
    EXPECT_NO_THROW(config.web.login = "456";);
    EXPECT_NO_THROW(config.web.password = "789";);

    std::cout << config.generate_config();

  }

}