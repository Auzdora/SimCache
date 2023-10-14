#include <unordered_map>

#pragma once
namespace SimCache {

template <typename Key, typename Value>
class LocalStorageEngine {
public:
  /**
   * @brief Insert Key Value pair into cache, if a key has already been inserted,
   * update the corresponding value
   *
   * @param key any-type key
   * @param value any-type value
   * @return bool, true if success, false otherwise
   */
  auto Insert(Key key, Value value) -> bool;

  /**
   * @brief Update Key Value pair in cache
   * @param key any-type key
   * @param[out] value any-type value
   * @return bool, true if success, false otherwise
   */
  auto Find(Key key, Value &value) -> bool;

  /**
   * @brief Delete Key Value pair into cache
   *
   * @param key any-type key
   * @param[out] value any-type value
   * @return bool, true if success, false otherwise
   */
  auto Delete(Key key, Value &value) -> bool;

  // Helper functions for testing
  auto GetCacheNum() const -> int { return cache_.size(); }

private:
  std::unordered_map<Key, Value> cache_;
};

} // namespace SimCahe