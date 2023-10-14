#include "server/rpc_stub.h"

namespace SimCache {

RPCStub::RPCStub(rest_rpc::rpc_service::rpc_server *rpc_server)
    : rpc_server_(rpc_server) {
  RegisterAllHandler();
}

RPCStub::RPCStub(rest_rpc::rpc_service::rpc_server *rpc_server,
                 CacheManager *cache_manager)
    : rpc_server_(rpc_server), cache_manager_(cache_manager) {
  RegisterAllHandler();
}

void RPCStub::RegisterAllHandler() {
  rpc_server_->register_handler(
      "Insert",
      [this](rest_rpc::rpc_service::rpc_conn conn, std::string key,
             std::string val) { return Insert(std::move(conn), key, val); });
  rpc_server_->register_handler(
      "Delete", [this](rest_rpc::rpc_service::rpc_conn conn, std::string key) {
        return Delete(std::move(conn), key);
      });
  rpc_server_->register_handler(
      "Find", [this](rest_rpc::rpc_service::rpc_conn conn, std::string key) {
        return Find(std::move(conn), key);
      });
}
} // namespace SimCache