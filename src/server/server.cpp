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
    : host_(host), port_(port), server_(), rpc_server_(9000, 2) {
  InitRouter();
  rpc_server_.register_handler("add", add);
}

/* -----------------Route methods------------------- */
void CacheServer::GetValue(const httplib::Request& req, httplib::Response& res) {
  std::cout << "get value" << std::endl;
  std::string key = req.matches[1];
  const char* me = std::getenv("ME");
  std::string me_str = me;
  if (std::stoi(me_str) == 0) {
    std::string other = std::to_string(std::stoi(me_str) + 1);
    std::string destination = "cache_server_" + other;
    std::string ip = resolve_hostname_to_ip(destination);
    rest_rpc::rpc_client client(ip, 9000);
    bool has_connected = client.connect();
    /*没有建立连接则退出程序*/
    if (!has_connected) {
        std::cout << "connect timeout" << std::endl;
        exit(-1);
    }
    // client.connect();
    int result = client.call<int>("add", 1, 2);
    std::cout << "add result " << result << std::endl;
  }
  const char* others = std::getenv("OTHERS");
  res.set_content("key is " + key + " " + "I am " + me + " " + "others " + others, "text/plain");
}

void CacheServer::InsertOrUpdate(const httplib::Request& req, httplib::Response& res) {
  auto json = nlohmann::json::parse(req.body);
  res.set_content(json.dump() + "\n", "application/json");
}

void CacheServer::Delete(const httplib::Request& req, httplib::Response& res) {
  // define delete post and corresponding logic
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


auto CacheServer::resolve_hostname_to_ip(const std::string& hostname) -> std::string {
  struct addrinfo hints{};
  struct addrinfo* result;
  char ipstr[INET_ADDRSTRLEN];

  hints.ai_family = AF_INET;  // 使用AF_INET来强制IPv4
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(hostname.c_str(), nullptr, &hints, &result);
  if (status != 0) {
      std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
      return "";
  }

  // 尽管可能有多个地址，我们只获取第一个
  if (result->ai_family == AF_INET) {
      struct sockaddr_in* ipv4 = (struct sockaddr_in*)result->ai_addr;
      inet_ntop(result->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
  } else {
      std::cerr << "No IPv4 address found." << std::endl;
      return "";
  }

  freeaddrinfo(result);
  return std::string(ipstr);
}
} // namespace SimCache