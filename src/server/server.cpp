#include "server/server.h"
#include "cpp_httplib/httplib.h"
#include <memory>

namespace SimCache {

CacheServer::CacheServer(const std::string &host, int port)
    : host_(host), port_(port), server_() {
  InitRouter();
}

/* -----------------Route methods------------------- */
void CacheServer::GetValue(const httplib::Request& req, httplib::Response& res) {
  std::string key = req.matches[1];
  res.set_content("key is " + key + "\n", "text/plain");
}

void CacheServer::InsertOrUpdate(const httplib::Request& req, httplib::Response& res) {
  auto json = nlohmann::json::parse(req.body);
  res.set_content(json.dump() + "\n", "application/json");
}

void CacheServer::Delete(const httplib::Request& req, httplib::Response& res) {

}
/* ------------------------------------------------- */

void CacheServer::InitRouter() {
  // Get methods
  router_.RegGet(R"(/(\w+))", GetValue);

  // Post methods
  router_.RegPost("/", InsertOrUpdate);

  // Delete methods
  router_.RegDelete(R"(/(\w+))", Delete);
}

} // namespace SimCache