module;

#include <gtest/gtest.h>
#include <gmock/gmock.h>

export module dsm.config.test;

import dsm.logger;
import dsm.config;

using ::testing::HasSubstr;
using ::testing::MatchesRegex;

export namespace ConfigTest {

  TEST(Test1, Constructor) {
    EXPECT_NO_THROW(Config config);
  }

  TEST(Test1, WebFields) {
    Config config = {};

    EXPECT_NO_THROW(config.settings.web.port = 123;);
    EXPECT_NO_THROW(config.settings.web.login = "456";);
    EXPECT_NO_THROW(config.settings.web.password = "789";);

    EXPECT_THAT(config.generate(), HasSubstr("port: 123"));

  }

  TEST(Test1, LoadConfig) {
    Config config = {};

    EXPECT_NO_THROW(config.load());
    EXPECT_TRUE(config.load());

  }

  TEST(Test1, SaveConfig) {
    Config config = {};

    EXPECT_NO_THROW(config.save());
  }

  TEST(Test1, LoadAfterChangeConfig) {
    Config config1 = {};

    auto port = config1.settings.web.port;
    config1.settings.web.port = 1;
    config1.save();

    Config config2 = {};
    config2.load();
    EXPECT_EQ(config2.settings.web.port, 1);

    config1.settings.web.port = port;
    config1.save();
  }

}