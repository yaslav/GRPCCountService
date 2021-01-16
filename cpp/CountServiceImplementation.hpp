#pragma once

#include <iostream>
#include <grpcpp/grpcpp.h>
#include "counter.grpc.pb.h"
#include "counter.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class CountServiceImplementation final : public counter::CountService::Service{
	Status sendRequest(ServerContext* context,
		const counter::CountRequest* request,
		counter::CountResponse* response
	) override {
		int count = request->count();
		std::cout << "Count received: " << count << std::endl;
		response->set_count(count + 1);
		return Status::OK;
	}
};