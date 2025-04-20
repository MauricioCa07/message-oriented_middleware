#pragma once
#include <grpcpp/grpcpp.h>
#include "../../protos/mom_to_mom/mom_to_mom.grpc.pb.h"


using grpc::ServerContext;
using grpc::Status;
using grpc::ServerBuilder;
using grpc::Server;


class communication_mom_stub {
private:
    std::unique_ptr<mom_to_mom::MOM_cluster_service::Stub> stub_;

public:
    communication_mom_stub(std::shared_ptr<grpc::Channel> channel)
        : stub_(mom_to_mom::MOM_cluster_service::NewStub(channel)) {}

    Status replicate_topic(const std::string& name, const std::string& owner, mom_to_mom::status* response);
    Status replicate_queue(const std::string& name, const std::string& owner, mom_to_mom::status* response);

    Status replicate_delete_queue(const std::string& name, const std::string& owner, mom_to_mom::status* response);
    Status replicate_delete_topic(const std::string& name, const std::string& owner, mom_to_mom::status* response);
    
    
    Status replicate_topic_subscription(const std::string&topic_name,const std::string&topic_owner,const std::string&queue_name,const std::string&queue_owner,mom_to_mom::status* response);
    Status replicate_topic_unsubscription(const std::string&topic_name,const std::string&topic_owner,const std::string&queue_name,const std::string&queue_owner,mom_to_mom::status* response);


    Status replicate_queue_message(const std::string& structure_name,const std::string& content,const std::string& sender,int64_t timestamp,bool persistent,mom_to_mom::status* response);
    Status replicate_topic_message(const std::string& structure_name,const std::string& content,const std::string& sender,int64_t timestamp,bool persistent,mom_to_mom::status* response);
    Status replicate_receive_queue_message(const std::string& name,const std::string& owner,mom_to_mom::structure_message* response);
    Status replicate_receive_topic_message(const std::string& topic_name,const std::string& topic_owner,const std::string& queue_name,const std::string& queue_owner,bool durable,mom_to_mom::structure_message* response);
};
