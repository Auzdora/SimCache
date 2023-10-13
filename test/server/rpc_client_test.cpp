#include <gtest/gtest.h>
#include "server/server.h"
#include <rpc/include/rest_rpc.hpp>

TEST(RPCTEST, ClientTest) {
    struct addrinfo hints{};
    struct addrinfo* result;
    char ipstr[INET6_ADDRSTRLEN];

    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo("localhost", nullptr, &hints, &result);
    if (status != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
    }

    for(struct addrinfo* p = result; p != nullptr; p = p->ai_next) {
        if (p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            inet_ntop(p->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
        }
        std::cout << "IP address: " << ipstr << std::endl;
    }
	std::cout << "final is " << ipstr << std::endl;
	rest_rpc::rpc_client client(ipstr, 9000);
	client.connect();

	int add_result = client.call<int>("add", 1, 2);
	std::cout << "add result " << add_result << std::endl;

	client.run();
	freeaddrinfo(result);
}