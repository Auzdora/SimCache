#include <cpp_httplib/httplib.h>
#include <json/include/nlohmann/json.hpp>
#include <string>
#include "server/router.h"

namespace SimCache {

class CacheServer {
public:
  /**
   * Constructor and deconstructor
   */
  CacheServer(const std::string &host = "localhost", int port = 1234);
  ~CacheServer() = default;

  /**
   * @brief Launch the server
   */
   void Start() { 
    router_.Route(server_);
    server_.listen(host_, port_);
  }

  /**
   * @brief Shut down the server
   */
   void Stop() { server_.stop(); }

  /**
   * Helper functions
   */
  auto GetHostName() const -> const std::string& { return host_; }
  auto GetPortNum() const -> int {return port_; }
  void SetPortNum(int new_port) { port_ = new_port; }

private:
  /**
   * @brief Server router which contains Get and Post method
   *
   * This function should be called in constructor.
   *
   * @param null
   * @return null
   */
  void InitRouter();

  /**
   * @brief Handle the get key-value pair request
   *
   * This function should be registered in router.
   *
   * @param null
   * @return null
   */
  static void GetValue(const httplib::Request& req, httplib::Response& res);

  /**
   * @brief Handle the post key-value pair request
   *
   * This function should be registered in router. If it don't have this kv pair,
   * insert into current server. If it already has, wherever it is, update its val.
   *
   * @param null
   * @return null
   */
  static void InsertOrUpdate(const httplib::Request& req, httplib::Response& res);

  /**
   * @brief Handle the delete key-value pair request
   *
   * This function should be registered in router. If found the kv pair, delete it.
   * Otherwise, return 0.
   *
   * @param null
   * @return null
   */
  static void Delete(const httplib::Request& req, httplib::Response& res);

  std::string host_;
  int port_;
  httplib::Server server_;
  Router router_;
};

} // namespace SimCache