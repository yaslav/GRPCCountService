// GRPCCountService.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include <grpcpp/grpcpp.h>
#include "counter.grpc.pb.h"
#include "counter.pb.h"

#include "GRPCCountService.h"


int main()
{
	counter::CountRequest req;
	req.set_count(10);
	std::cout << req.count() << std::endl;
	return 0;
}
