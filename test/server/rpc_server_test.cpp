#include <gtest/gtest.h>
#include "server/rpc_stub.h"
#include <rpc/include/rest_rpc.hpp>

//1.先定义person对象
struct person {
    int id;
    std::string name;
    int age;

    MSGPACK_DEFINE(id, name, age);
};
struct dummy{
	int add(rest_rpc::rpc_service::rpc_conn conn, int a, int b) { 
        std::cout << "get the request, add and return" << std::endl;
        return a + b;
    }
};

//2.提供并服务
person get_person(rest_rpc::rpc_service::rpc_conn conn) {
    return { 1, "tom", 20 };
}

TEST(RPCTEST, SimpleTest) {
	rest_rpc::rpc_service::rpc_server server(9000, std::thread::hardware_concurrency());
    SimCache::RPCStub rpc_stub(&server);

	// dummy d;
	// server.register_handler("add", &dummy::add, &d);
	
	server.run();
}