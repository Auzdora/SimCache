#include "server/server.h"
#include "cpp_httplib/httplib.h"
#include <memory>
#include <cstdlib>
#include <string>

namespace SimCache {
int add(rest_rpc::rpc_service::rpc_conn conn, int a, int b) { 
  std::cout << "get the request, add and return" << std::endl;
  return a + b;
}

CacheServer::CacheServer(const std::string &host, int port)
    : host_(host), port_(port), server_(), rpc_server_(9000, 2), cache_manager_(), rpc_stub_(&rpc_server_, &cache_manager_) {
  InitRouter();
  rpc_server_.register_handler("add", add);

  const char* me = std::getenv("ME");
  if (me) {
    std::string str_me = me;
    self_token_ = std::stoi(str_me);
    std::cout << "server token: " << self_token_ << std::endl;
    cache_manager_.SetHostNo(self_token_);
  }
  const char* total = std::getenv("TOTAL");
  if (total) {
    std::string str_total = total;
    server_nums_ = std::stoi(str_total);
    std::cout << "system total server number: " << server_nums_ << std::endl;
    cache_manager_.SetHostNum(server_nums_);
  }

}

/* -----------------Route methods------------------- */
void CacheServer::GetValue(const httplib::Request& req, httplib::Response& res) {
  std::string key = req.matches[1];
  std::string val;
  bool ans = cache_manager_.Find(key, val);
  if (!ans) {
    res.status = 404;
    return;
  }
  // Define a JSON object
  nlohmann::json j = {
      {key, val}
  };
  res.status = 200;
  res.set_content(j.dump() + "\n" , "application/json");
}

void CacheServer::InsertOrUpdate(const httplib::Request& req, httplib::Response& res) {
  auto json = nlohmann::json::parse(req.body);
  for (auto& [key, value] : json.items()) {
    std::cout << "key " << key << " value " << value << std::endl;
    cache_manager_.Insert(key, value);
  }
  res.set_content(json.dump() + "\n", "application/json");
}

void CacheServer::Delete(const httplib::Request& req, httplib::Response& res) {
  // define delete post and corresponding logic
  std::string key = req.matches[1];
  std::string val;
  bool ans = cache_manager_.Delete(key, val);
  if (ans) {
    std::cout << "delete!" << std::endl;
    res.status = 200;
    res.set_content("1\n", "text/plain");
  } else {
    std::cout << "not delete" << std::endl;
    res.status = 200;
    res.set_content("0\n", "text/plain");
  }
}
/* ------------------------------------------------- */

void CacheServer::InitRouter() {
  // Get methods
  router_.RegGet(R"(/([\w\-]+))", [this](const httplib::Request& req, httplib::Response& res) {
    this->GetValue(req, res);
  });

  // Post methods
  router_.RegPost("/", [this](const httplib::Request& req, httplib::Response& res) {
    this->InsertOrUpdate(req, res);
  });

  // Delete methods
  router_.RegDelete(R"(/([\w\-]+))", [this](const httplib::Request& req, httplib::Response& res) {
    this->Delete(req, res);
  });
}

} // namespace SimCache