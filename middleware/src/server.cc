#include <grpcpp/grpcpp.h>
#include "mom_impl/mom_impl.h"
#include "mom_to_mom/communication_mom_to_mom.h"
#include <iostream>

int main() {
    mom_impl mom_service;

    communication_mom_to_mom replication_service(
        mom_service.get_queues(),
        mom_service.get_topics()
    );


    grpc::ServerBuilder builder;
    const std::string address = "0.0.0.0:34600";
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());



    builder.RegisterService(&mom_service);
    builder.RegisterService(&replication_service);


    
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "MOM node listening on " << address << " …\n";
    server->Wait();

    return 0;
}
