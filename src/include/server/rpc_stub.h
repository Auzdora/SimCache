#include <rpc/include/rest_rpc.hpp>
#include "store/storage_engine.h"
#include "cache/cache_manager.h"

namespace SimCache {

struct Result {
  bool ans;
  std::string val;

  MSGPACK_DEFINE(ans, val);
};

class RPCStub {
public:
  explicit RPCStub(rest_rpc::rpc_service::rpc_server *rpc_server);
  explicit RPCStub(rest_rpc::rpc_service::rpc_server *rpc_server, CacheManager *cache_manager);
  ~RPCStub() = default;
private:
  void RegisterAllHandler();
  bool Insert(rest_rpc::rpc_service::rpc_conn conn, std::string key, std::string val) {
    std::cout << "get the request, insert and return" << std::endl;
    return cache_manager_->Insert(key, val);
  }
  Result Find(rest_rpc::rpc_service::rpc_conn conn, std::string key) {
    std::cout << "get the request, Find and return" << std::endl;
    std::string val;
    bool ans = cache_manager_->Find(key, val);
    return {ans, val};
  }
  Result Delete(rest_rpc::rpc_service::rpc_conn conn, std::string key) {
    std::cout << "get the request, Delete and return" << std::endl;
    std::string val;
    bool ans = cache_manager_->Delete(key, val);
    return {ans, val};
  }
  rest_rpc::rpc_service::rpc_server *rpc_server_;
  CacheManager *cache_manager_;
};

} // namespace SimCache