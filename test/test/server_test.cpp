#include <gtest/gtest.h>
#include "server/server.h"

TEST(BasicTest, PrintTest) {
    test();
}

TEST(BasicTest, ServerTest) {
    EXPECT_EQ(0, RunServer());
}