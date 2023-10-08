#include "server/router.h"

namespace SimCache {

void Router::RegGet(
    const std::string &path,
    std::function<void(const httplib::Request &, httplib::Response &)>
        handler) {
  get_handlers_[path] = handler;
}

void Router::RegPost(
    const std::string &path,
    std::function<void(const httplib::Request &, httplib::Response &)>
        handler) {
  post_handlers_[path] = handler;
}

void Router::RegDelete(
    const std::string &path,
    std::function<void(const httplib::Request &, httplib::Response &)>
        handler) {
  delete_handlers_[path] = handler;
}

void Router::Route(httplib::Server &server) {
  for (const auto &[path, function] : get_handlers_) {
    server.Get(path, function);
  }
  for (const auto &[path, function] : post_handlers_) {
    server.Post(path, function);
  }
  for (const auto &[path, function] : delete_handlers_) {
    server.Delete(path, function);
  }
}

} // namespace SimCache