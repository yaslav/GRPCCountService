// GRPCCountService.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include <string>
#include <grpcpp/grpcpp.h>
#include "counter.grpc.pb.h"

#include "GRPCCountService.h"
#include "CountServiceImplementation.hpp"


void RunServer(std::string address) {
	CountServiceImplementation service;
	grpc::ServerBuilder builder;
	builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Listening on port: " << address << std::endl;

	server->Wait();
}
int main()
{

	RunServer("0.0.0.0:4567");
	return 0;
}


