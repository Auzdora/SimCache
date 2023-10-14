#include "cache/cache_manager.h"
#include <stdexcept>

namespace SimCache {

CacheManager::CacheManager(int host_no, int host_num, int rpc_port,
                           std::string host_name_prefix)
    : host_no_(host_no), host_num_(host_num), rpc_port_(rpc_port),
      host_name_prefix_(host_name_prefix) {}

auto CacheManager::Insert(std::string key, std::string value) -> bool {
  int num = mod_hash(key);

  // key-value pair needs to store in local cache
  if (num == host_no_) {
    bool success = local_storage_engine_.Insert(key, value);
    return success;
  }

  // key-value pair needs to store other server's cache
  std::string dest_host_name = host_name_prefix_ + std::to_string(num);
  std::string host_ip_addr = resolve_hostname_to_ip(dest_host_name);

  rest_rpc::rpc_client client(host_ip_addr, rpc_port_);
  bool has_connected = client.connect();
  if (!has_connected) {
    throw std::runtime_error("connect failed");
  }

  // call rpc insert method
  return true;
}

auto CacheManager::Find(std::string key, std::string &value) -> bool {
  int num = mod_hash(key);

  // key-value pair needs to store in local cache
  if (num == host_no_) {
    bool success = local_storage_engine_.Find(key, value);
    return success;
  }

  // key-value pair needs to store other server's cache
  std::string dest_host_name = host_name_prefix_ + std::to_string(num);
  std::string host_ip_addr = resolve_hostname_to_ip(dest_host_name);

  rest_rpc::rpc_client client(host_ip_addr, rpc_port_);
  bool has_connected = client.connect();
  if (!has_connected) {
    throw std::runtime_error("connect failed");
  }

  // call rpc find method
  return true;
}

auto CacheManager::Delete(std::string key, std::string &value) -> bool {
  int num = mod_hash(key);

  // key-value pair needs to store in local cache
  if (num == host_no_) {
    bool success = local_storage_engine_.Delete(key, value);
    return success;
  }

  // key-value pair needs to store other server's cache
  std::string dest_host_name = host_name_prefix_ + std::to_string(num);
  std::string host_ip_addr = resolve_hostname_to_ip(dest_host_name);

  rest_rpc::rpc_client client(host_ip_addr, rpc_port_);
  bool has_connected = client.connect();
  if (!has_connected) {
    throw std::runtime_error("connect failed");
  }

  // call rpc find method
  return true;
}

auto CacheManager::resolve_hostname_to_ip(const std::string &hostname)
    -> std::string {
  struct addrinfo hints {};
  struct addrinfo *result;
  char ipstr[INET_ADDRSTRLEN];

  hints.ai_family = AF_INET; // 使用AF_INET来强制IPv4
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(hostname.c_str(), nullptr, &hints, &result);
  if (status != 0) {
    std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
    return "";
  }

  // 尽管可能有多个地址，我们只获取第一个
  if (result->ai_family == AF_INET) {
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
    inet_ntop(result->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
  } else {
    std::cerr << "No IPv4 address found." << std::endl;
    return "";
  }

  freeaddrinfo(result);
  return std::string(ipstr);
}

} // namespace SimCache