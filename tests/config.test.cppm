module;

#include <gtest/gtest.h>
#include <gmock/gmock.h>

export module config.test;

import logger;
import config;

using ::testing::HasSubstr;
using ::testing::MatchesRegex;

export namespace ConfigTest {

  TEST(Test1, Constructor) {
    EXPECT_NO_THROW(Config config);
  }

  TEST(Test1, WebFields) {
    Config config = {};

    EXPECT_NO_THROW(config.web.port = 123;);
    EXPECT_NO_THROW(config.web.login = "456";);
    EXPECT_NO_THROW(config.web.password = "789";);

    EXPECT_THAT(config.generate_config(), HasSubstr("port: 123"));

  }

  TEST(Test1, LoadFile) {
    Config config = {};

    EXPECT_NO_THROW(config.load_config());

  }

}