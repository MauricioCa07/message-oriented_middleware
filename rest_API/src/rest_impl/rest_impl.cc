#include "rest_impl.h"

    
rest_impl::rest_impl(std::shared_ptr<grpc::Channel> channel)
        : stub_(mom::MOM_service::NewStub(channel)) {}


bool rest_impl::create_queue(const std::string& name, std::string& owner){
    grpc::ClientContext context;

    mom::queue_config request;
    request.set_name(name);
    request.set_owner(owner);

    mom::status response;
    grpc::Status status = stub_->create_queue(&context, request, &response);
    if (status.ok()) {
        bool success = response.success();
        std::string  message = response.message();
        return true;
    } 

    std::cout << "GetUserInfo RPC failed: " << status.error_message() << std::endl;
    return false;
    }


bool rest_impl::delete_queue(const std::string& name, std::string& owner){
    grpc::ClientContext context;


    mom::queue_identifier request;
    request.set_name(name);
    request.set_owner(owner);


    mom::status response;
    grpc::Status status = stub_->delete_queue(&context, request, &response);

    if (status.ok()) {
        bool success = response.success();
        std::string  message = response.message();
        return true;
    } 

    std::cout << "GetUserInfo RPC failed: " << status.error_message() << std::endl;
    return false;
}

crow::json::wvalue rest_impl::list_queues(){
    grpc::ClientContext context;

    mom::NodeID request;
    request.set_node_id("0");

    mom::queues_response response;

    grpc::Status status = stub_->list_queues(&context, request, &response);

    crow::json::wvalue result;

    if (status.ok() && response.success()) {
        result["success"] = true;
        result["message"] = response.message();
    
        int idx = 0;
        for (const auto& queue : response.queues()) {
            crow::json::wvalue queue_json;
            queue_json["name"] = queue.name();
            queue_json["owner"] = queue.owner();
            queue_json["creation_timestamp"] = queue.creation_timestamp();
            queue_json["message_count"] = queue.message_count();
    
            result["queues"][idx++] = std::move(queue_json); 
        }
    
        return result;
    }

    result["success"] = false;
    result["message"] = status.ok() ? response.message() : status.error_message();
    return result;
}


bool rest_impl::create_topic(const std::string& name, std::string& owner){
    grpc::ClientContext context;


    mom::topic_config request;
    request.set_name(name);
    request.set_owner(owner);


    mom::status response;
    grpc::Status status = stub_->create_topic(&context, request, &response);
    if (status.ok()) {
        bool success = response.success();
        std::string  message = response.message();
        return true;
    } 

    std::cout << "GetUserInfo RPC failed: " << status.error_message() << std::endl;
    return false;
    }


bool rest_impl::delete_topic(const std::string& name, std::string& owner){
    grpc::ClientContext context;

    mom::topic_identifier request;
    request.set_name(name);
    request.set_owner(owner);


    mom::status response;
    grpc::Status status = stub_->delete_topic(&context, request, &response);

    if (status.ok()) {
        bool success = response.success();
        std::string  message = response.message();
        return true;
    } 

    std::cout << "GetUserInfo RPC failed: " << status.error_message() << std::endl;
    return false;
    }

crow::json::wvalue rest_impl::list_topics(){

    grpc::ClientContext context;

    mom::NodeID request;
    request.set_node_id("0");

    mom::topics_response response;

    grpc::Status status = stub_->list_topics(&context, request, &response);

    crow::json::wvalue result;

    if (status.ok() && response.success()) {
        result["success"] = true;
        result["message"] = response.message();

        int idx = 0;
        for (const auto& topic : response.topics()) {
            crow::json::wvalue topic_json;
            topic_json["name"] = topic.name();
            topic_json["owner"] = topic.owner();
            topic_json["creation_timestamp"] = topic.creation_timestamp();
            topic_json["message_count"] = topic.message_count();

            result["topics"][idx++] = std::move(topic_json);
        }

        return result;
    }

    result["success"] = false;
    result["message"] = status.ok() ? response.message() : status.error_message();
    return result;
}

bool rest_impl::subscribe_topic(const std::string& topic_name, std::string& topic_owner,
                        const std::string& queue_name,const std::string& queue_owner){
    grpc::ClientContext context;

    mom::topic_subscription request;
    request.set_topic_name(topic_name);
    request.set_topic_owner(topic_owner);
    request.set_subscriber_queue_name(queue_name);
    request.set_subscriber_queue_owner(queue_owner);

    mom::status response;                
    grpc::Status status = stub_->subscribe_topic(&context, request, &response);

    if (status.ok()) {
        bool success = response.success();
        std::string  message = response.message();
        return true;
    } 

    std::cout << "GetUserInfo RPC failed: " << status.error_message() << std::endl;
    return false;

}


bool rest_impl::unsubscribe_topic(const std::string& topic_name, std::string& topic_owner,
    const std::string& queue_name,const std::string& queue_owner){
    grpc::ClientContext context;

    mom::topic_subscription request;
    request.set_topic_name(topic_name);
    request.set_topic_owner(topic_owner);
    request.set_subscriber_queue_name(queue_name);
    request.set_subscriber_queue_owner(queue_owner);

    mom::status response;                
    grpc::Status status = stub_->unsubscribe_topic(&context, request, &response);

    if (status.ok()) {
    bool success = response.success();
    std::string  message = response.message();
    return true;
    } 

    std::cout << "GetUserInfo RPC failed: " << status.error_message() << std::endl;
    return false;

}

bool rest_impl::get_node_state(){
    mom::node_status request;
    mom::node_status response; 
    
    grpc::ClientContext context;

    request.set_active(false);

    grpc::Status status = stub_->get_node_state(&context, request, &response);

    return response.active();

}


bool rest_impl::give_node_information(int i, std::string ip, int port,bool is_leader){
   grpc::ClientContext context;
    
    mom::node_info request;
    request.set_node_id(i);
    request.set_ip(ip);
    request.set_port(port);
    request.set_leader(is_leader);
    
    mom::status response;                
    grpc::Status status = stub_->join_cluster(&context, request, &response);

    if (status.ok()) {
        bool success = response.success();
        std::string  message = response.message();
        return true;
    } 
    return false;
}

bool rest_impl::give_cluster_information(int i, std::string ip, int port,bool is_leader){
    grpc::ClientContext context;
    
    mom::node_info request;
    request.set_node_id(i);
    request.set_ip(ip);
    request.set_port(port);
    request.set_leader(is_leader);
    
    mom::status response;                
    grpc::Status status = stub_->set_cluster(&context, request, &response);

    if (status.ok()) {
        bool success = response.success();
        std::string  message = response.message();
        return true;
    } 
    return false;
}


bool rest_impl::send_queue_message(const std::string& structure_name, const std::string& content,
                                   const std::string& sender){
    grpc::ClientContext context;
    mom::structure_message request;

    request.set_structure_name(structure_name);
    request.set_content(content);
    request.set_sender(sender);

    mom::message_status response;                
    grpc::Status status = stub_->send_queue_message(&context, request, &response);

    if (status.ok()) {
        bool success = response.success();
        std::string  message = response.message();
        return true;
    } 
    return false;
}

bool rest_impl::request_queue_message(const std::string& queue_name, const std::string& queue_owner, mom::structure_message* out_response) {
    grpc::ClientContext context;
    mom::queue_identifier request;

    request.set_name(queue_name);
    request.set_owner(queue_owner);

    grpc::Status status = stub_->receive_queue_message(&context, request, out_response);
    return status.ok();
}



bool rest_impl::send_topic_message(const std::string& topic_name, const std::string& content, const std::string& sender) {
    grpc::ClientContext context;
    mom::structure_message request;

    request.set_structure_name(topic_name);
    request.set_content(content);
    request.set_sender(sender);
    request.set_persistent(true);

    mom::message_status response;
    grpc::Status status = stub_->publish_topic_message(&context, request, &response);

    return status.ok() && response.success();
}


bool rest_impl::request_topic_message(const std::string& topic_name, const std::string& topic_owner, mom::structure_message* out_response) {
    grpc::ClientContext context;
    mom::topic_subscription request;

    request.set_topic_name(topic_name);
    request.set_topic_owner(topic_owner);

    grpc::Status status = stub_->receive_topic_message(&context, request, out_response);
    return status.ok();
}

