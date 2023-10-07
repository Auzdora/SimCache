#include "server/server.h"

void test() {
    std::cout << "hello world" << std::endl;
}

int RunServer() {
    httplib::Server svr;
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {

        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/exit", [&](const httplib::Request&, httplib::Response& res) {
        svr.stop();
    });

    svr.listen("localhost", 1234);

    return 0;
}
namespace SimCache {

} // namespace SimCache