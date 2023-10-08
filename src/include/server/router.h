#include "cpp_httplib/httplib.h"
#include <functional>
#include <string>
#include <unordered_map>
namespace SimCache {

class Router {
public:
  /**
   * @brief Register the Get method
   */
  void RegGet(const std::string &path,
              std::function<void(const httplib::Request &, httplib::Response &)>
                  handler);
  /**
   * @brief Register the Post method
   */
  void
  RegPost(const std::string &path,
          std::function<void(const httplib::Request &, httplib::Response &)>
              handler);
  /**
   * @brief Register the Delete method
   */
  void
  RegDelete(const std::string &path,
            std::function<void(const httplib::Request &, httplib::Response &)>
                handler);

  /**
   * @brief Register handlers to server
   */
   void Route(httplib::Server &server);

private:
  std::unordered_map<std::string, std::function<void(const httplib::Request &,
                                                     httplib::Response &)>>
      get_handlers_;
  std::unordered_map<std::string, std::function<void(const httplib::Request &,
                                                     httplib::Response &)>>
      post_handlers_;
  std::unordered_map<std::string, std::function<void(const httplib::Request &,
                                                     httplib::Response &)>>
      delete_handlers_;
};

} // namespace SimCache