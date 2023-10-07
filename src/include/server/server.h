#include <iostream>
#include <cpp_httplib/httplib.h>
#include <json/include/nlohmann/json.hpp>

void test();
int RunServer();
namespace SimCache {

class CacheServer {
public:
  CacheServer(const std::string& host, int port);


private:
  std::string host_;
  int port_;
  httplib::Server server_;
};

} // namespace SimCache