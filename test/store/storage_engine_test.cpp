#include "store/storage_engine.h"
#include <gtest/gtest.h>
#include <string>

TEST(StorageTest, SimpleIntTest) {
  auto storage = new SimCache::LocalStorageEngine<int, int>;

  int insert_num = 100;
  for (int i = 0; i < insert_num; i++) {
    int val;
    storage->Insert(i, i+1);
    storage->Find(i, val);
    EXPECT_EQ(val, i+1);
  }

  // now delete some record
  for (int i = 0; i < 100; i+=2) {
    int val;
    storage->Delete(i, val);
    EXPECT_EQ(val, i+1);
  }

  // check the final size
  EXPECT_EQ(storage->GetCacheNum(), 50);
}

TEST(StorageTest, SimpleStringTest) {
  auto storage = new SimCache::LocalStorageEngine<std::string, int>;

  int insert_num = 100;
  for (int i = 0; i < insert_num; i++) {
    int val;
    storage->Insert(std::to_string(i), i+1);
    storage->Find(std::to_string(i), val);
    EXPECT_EQ(val, i+1);
  }

  // now delete some record
  for (int i = 0; i < 100; i+=2) {
    int val;
    storage->Delete(std::to_string(i), val);
    EXPECT_EQ(val, i+1);
  }

  EXPECT_EQ(storage->GetCacheNum(), 50);
}