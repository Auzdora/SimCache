#include "store/storage_engine.h"

namespace SimCache {

template <typename Key, typename Value>
auto LocalStorageEngine<Key, Value>::Insert(Key key, Value value) -> bool {
  cache_[key] = value;
  
  return true;
}

template <typename Key, typename Value>
auto LocalStorageEngine<Key, Value>::Find(Key key, Value &value) -> bool {
  auto it = cache_.find(key);

  if (it == cache_.end()) {
    return false;
  }

  value = cache_[key];
  return true;
}

template <typename Key, typename Value>
auto LocalStorageEngine<Key, Value>::Delete(Key key, Value &value) -> bool {
  auto it = cache_.find(key);

  if (it != cache_.end()) {
    value = it->second;
    cache_.erase(it);
  }
  
  return true;
}

template class LocalStorageEngine<int, int>;
template class LocalStorageEngine<std::string, int>;
template class LocalStorageEngine<std::string, std::string>;

} // namespace SimCache