#include "server/server.h"
#include <cpp_httplib/httplib.h>
#include <json/include/nlohmann/json.hpp>

int main() {
    SimCache::CacheServer server("0.0.0.0", 9527);
    std::cout << "starting server ... " << std::endl;
    server.Start();
    std::cout << "Goodbye!" << std::endl;
    return 0;
}