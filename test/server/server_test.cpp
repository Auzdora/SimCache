#include <gtest/gtest.h>
#include "server/server.h"

TEST(ServerTest, SimpleTest1) {
    SimCache::CacheServer svr{};
    svr.Start();
}