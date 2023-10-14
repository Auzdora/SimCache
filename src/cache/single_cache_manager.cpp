#include "cache/single_cache_manager.h"
#include <stdexcept>

namespace SimCache {

SingleCacheManager::SingleCacheManager(int rpc_port,
                           std::string host_name_prefix)
    : rpc_port_(rpc_port),
      host_name_prefix_(host_name_prefix) {}

auto SingleCacheManager::Insert(std::string key, std::string value) -> bool {
bool success = local_storage_engine_.Insert(key, value);
return success;
}

auto SingleCacheManager::Find(std::string key, std::string &value) -> bool {
bool success = local_storage_engine_.Find(key, value);
return success;
}

auto SingleCacheManager::Delete(std::string key, std::string &value) -> bool {
bool success = local_storage_engine_.Delete(key, value);
return success;
}

} // namespace SimCache