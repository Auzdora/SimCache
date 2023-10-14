#include "store/storage_engine.h"
#include <exception>
#include <rpc/include/rest_rpc.hpp>
#include <stdexcept>

#pragma once

namespace SimCache {

/** TODO: consider add template coding technique to let
 * cache manager handle any type of KV pairs.
 * For now, CaccheManager only handles string key and string value
 */

class CacheManager {
public:
  explicit CacheManager(
                        int rpc_port=9000, std::string host_name_prefix = "cache_server_");
  ~CacheManager() = default;

  void SetHostNo(int host_no) { host_no_ = host_no; }
  void SetHostNum(int host_num) {host_num_ = host_num; }
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
  /**
   * @brief Hash function
   *
   * To compute the destination server token
   *
   * @param null
   * @return null
   */
  inline auto mod_hash(std::string key) -> int {
    int num = get_key_num(key);
    return num % host_num_;
  }

  /**
   * @brief Parse the int number from the string key
   *
   * This function is helper function for mod_hash
   *
   * @param key string key
   * @return num parsed from key
   */
  auto get_key_num(std::string key) -> int {
    std::size_t pos = key.find('-');
    if (pos == std::string::npos) {
      throw std::invalid_argument("No number found in string key");
    }
    int num = std::stoi(key.substr(pos + 1));
    return num;
  }

  /**
   * @brief Add DNS sovler
   *
   * SimCache use simple rpc framework, which is rest_rpc.
   * https://github.com/qicosmos/rest_rpc
   * But rest rpc does not support automatic DNS solving.
   * The method defined here as a helper function.
   *
   * @param hostname the name of host, not ip address
   * @return the corresponding ip address based on the name of host
   */
  auto resolve_hostname_to_ip(const std::string &hostname) -> std::string;

  LocalStorageEngine<std::string, std::string>
      local_storage_engine_; // local sotarge engine
  int host_no_;              // indicate the exclusive token of current server
  int host_num_;             // indicate the number of servers
  int rpc_port_;             // rpc port
  std::string host_name_prefix_; // the prefix name of the hos
};

} // namespace SimCache