#include "communication_mom_stub.h"

Status communication_mom_stub::replicate_topic(const std::string& name, const std::string& owner, mom_to_mom::status* response) {
    grpc::ClientContext context;
    mom_to_mom::topic request;
    request.set_topic_name(name);
    request.set_topic_owner(owner);

    return stub_->replicate_topic(&context, request, response);
}

Status communication_mom_stub::replicate_queue(const std::string& name, const std::string& owner, mom_to_mom::status* response) {
    grpc::ClientContext context;
    mom_to_mom::queue request;
    request.set_queue_name(name);
    request.set_queue_owner(owner);

    return stub_->replicate_queue(&context, request, response);
}

Status communication_mom_stub::replicate_delete_queue(const std::string& name, const std::string& owner, mom_to_mom::status* response){
    grpc::ClientContext context;
    mom_to_mom::queue request;
    request.set_queue_name(name);
    request.set_queue_owner(owner);

    return stub_->replicate_delete_queue(&context, request, response);
}

Status communication_mom_stub::replicate_delete_topic(const std::string& name, const std::string& owner, mom_to_mom::status* response){
    grpc::ClientContext context;
    mom_to_mom::topic request;
    request.set_topic_name(name);
    request.set_topic_owner(owner);

    return stub_->replicate_delete_topic(&context, request, response);
}



Status communication_mom_stub::replicate_topic_subscription(const std::string&topic_name,const std::string&topic_owner,                                                          const std::string&queue_name,const std::string&queue_owner,mom_to_mom::status* response){
    grpc::ClientContext context;
    mom_to_mom::topic_subscription request;
    request.set_topic_name(topic_name);
    request.set_topic_owner(topic_owner);

    request.set_subscriber_queue_name(queue_name);
    request.set_subscriber_queue_owner(queue_owner);


    return stub_->replicate_topic_subscription(&context, request, response);

}

Status communication_mom_stub::replicate_topic_unsubscription(const std::string&topic_name,const std::string&topic_owner,const std::string&queue_name,const std::string&queue_owner,mom_to_mom::status* response){
    grpc::ClientContext context;
    mom_to_mom::topic_subscription request;
    request.set_topic_name(topic_name);
    request.set_topic_owner(topic_owner);

    request.set_subscriber_queue_name(queue_name);
    request.set_subscriber_queue_owner(queue_owner);


    return stub_->replicate_topic_unsubscription(&context, request, response);

}


Status communication_mom_stub::replicate_queue_message(const std::string& structure_name,
    const std::string& content,
    const std::string& sender,
    int64_t timestamp,
    bool persistent,
    mom_to_mom::status* response) {
grpc::ClientContext context;
mom_to_mom::structure_message request;

request.set_structure_name(structure_name);
request.set_content(content);
request.set_sender(sender);
request.set_timestamp(timestamp);
request.set_persistent(persistent);

return stub_->replicate_queue_message(&context, request, response);
}



Status communication_mom_stub::replicate_topic_message(const std::string& structure_name,
    const std::string& content,
    const std::string& sender,
    int64_t timestamp,
    bool persistent,
    mom_to_mom::status* response) {
grpc::ClientContext context;
mom_to_mom::structure_message request;

request.set_structure_name(structure_name);
request.set_content(content);
request.set_sender(sender);
request.set_timestamp(timestamp);
request.set_persistent(persistent);

return stub_->replicate_topic_message(&context, request, response);
}



Status communication_mom_stub::replicate_receive_queue_message(const std::string& name,
    const std::string& owner,
    mom_to_mom::structure_message* response) {
grpc::ClientContext context;
mom_to_mom::queue_identifier request;

request.set_name(name);
request.set_owner(owner);

return stub_->replicate_receive_queue_message(&context, request, response);
}



Status communication_mom_stub::replicate_receive_topic_message(const std::string& topic_name,
    const std::string& topic_owner,
    const std::string& queue_name,
    const std::string& queue_owner,
    bool durable,
    mom_to_mom::structure_message* response) {
grpc::ClientContext context;
mom_to_mom::topic_subscription request;

request.set_topic_name(topic_name);
request.set_topic_owner(topic_owner);
request.set_subscriber_queue_name(queue_name);
request.set_subscriber_queue_owner(queue_owner);
request.set_durable(durable);

return stub_->replicate_receive_topic_message(&context, request, response);
}
