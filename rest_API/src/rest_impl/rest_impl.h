#pragma once
#include "string"
#include <grpcpp/grpcpp.h>
#include "../../protos/rest_api/mom.grpc.pb.h"
#include "../../protos/rest_api/mom.pb.h"
#include "crow.h"
#include "../node/node_impl.h"

class rest_impl {
    private:
    std::unique_ptr<mom::MOM_service::Stub> stub_;

    public:
        
    rest_impl(std::shared_ptr<grpc::Channel> channel);



    bool create_queue(const std::string& name, std::string& owner);


    bool delete_queue(const std::string& name, std::string& owner);


    bool create_topic(const std::string& name, std::string& owner);

    crow::json::wvalue list_queues();

    crow::json::wvalue list_topics();

    bool delete_topic(const std::string& name, std::string& owner);
    
    bool subscribe_topic(const std::string& topic_name, std::string& topic_owner,
                         const std::string& queue_name,const std::string& queue_owner);

    bool unsubscribe_topic(const std::string& topic_name, std::string& topic_owner,
        const std::string& queue_name,const std::string& queue_owner);

    bool get_node_state();

    bool give_node_information(int i, std::string ip, int port,bool is_leader);

    bool give_cluster_information(int i, std::string ip, int port,bool is_leader);

    bool send_queue_message(const std::string& structure_name, const std::string& content,
        const std::string& sender);

    bool request_queue_message(const std::string& queue_name, const std::string& queue_owner, mom::structure_message* out_response);


    bool send_topic_message(const std::string& topic_name, const std::string& content, const std::string& sender);
    
    bool request_topic_message(const std::string& topic_name, const std::string& topic_owner, mom::structure_message* out_response);


};