#include "store/storage_engine.h"
#include <exception>
#include <rpc/include/rest_rpc.hpp>
#include <stdexcept>

namespace SimCache {

/** TODO: consider add template coding technique to let
 * cache manager handle any type of KV pairs.
 * For now, CaccheManager only handles string key and string value
 */

class SingleCacheManager {
public:
  explicit SingleCacheManager(
                        int rpc_port=9000, std::string host_name_prefix = "cache_server_");
  ~SingleCacheManager() = default;
  /**
   * @brief Insert the key value pair into memory cache
   *
   * Should be called by the upper system. First compute the key
   * mod using mod_hash, if the number is equal to host_no_, insert
   * key value pair on local storage. Otherwise, send rpc reqeust then
   * insert into destination server.
   *
   * @param key string
   * @param value string
   * @return insert success return true, otherwise return false
   */
  auto Insert(std::string key, std::string value) -> bool;

  /**
   * @brief Find the key value pair from SimCache
   *
   * Should be called by the upper system. First compute the key
   * mod using mod_hash, if the number is equal to host_no_, find
   * the value on local storage. Otherwise, send rpc reqeust then
   * return.
   *
   * @param key string
   * @param value string
   * @return find success return true, otherwise return false
   */
  auto Find(std::string key, std::string &value) -> bool;

  /**
   * @brief Delete the key value pair in SimCache
   *
   * Should be called by the upper system. First compute the key
   * mod using mod_hash, if the number is equal to host_no_, delete
   * key value pair on local storage. Otherwise, send rpc reqeust then
   * delete in the destination server.
   *
   * @param null
   * @return null
   */
  auto Delete(std::string key, std::string &value) -> bool;

private:

  LocalStorageEngine<std::string, std::string>
      local_storage_engine_; // local sotarge engine
  int rpc_port_;             // rpc port
  std::string host_name_prefix_; // the prefix name of the hos
};

} // namespace SimCache