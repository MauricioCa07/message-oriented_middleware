
#include "communication_mom_to_mom.h"


    Status communication_mom_to_mom::replicate_topic(::grpc::ServerContext* context, const ::mom_to_mom::topic* request, ::mom_to_mom::status* response){ 
        
        std::string name = request->topic_name();
        std::string owner = request->topic_owner();

        topic_obj new_topic;

        new_topic.set_topic_name(name);
        new_topic.set_topic_owner(owner);

        this->topics.add_topic_to_list(new_topic);

        response->set_success(true);
        response->set_message("Topic replicated succesfull");
        
        
        return grpc::Status::OK;
    }


    Status communication_mom_to_mom::replicate_queue(::grpc::ServerContext* context, const ::mom_to_mom::queue* request, ::mom_to_mom::status* response){ 
        std::string name = request->queue_name();
        std::string owner = request->queue_owner();

        queue_obj new_topic;

        new_topic.set_queue_name(name);
        new_topic.set_queue_owner(owner);

        this->queues.add_queue_to_list(new_topic);

        response->set_success(true);
        response->set_message("Topic replicated succesfull");
        
        
        return grpc::Status::OK;
        
    }


    Status communication_mom_to_mom::replicate_delete_queue(::grpc::ServerContext* context, const ::mom_to_mom::queue* request, ::mom_to_mom::status* response){ 
        this->queues.delete_queue_from_list(request->queue_name(),request->queue_owner());
        return grpc::Status::OK;
    }
    Status communication_mom_to_mom::replicate_delete_topic(::grpc::ServerContext* context, const ::mom_to_mom::topic* request, ::mom_to_mom::status* response){ 
        this->topics.delete_topic_from_list(request->topic_name(),request->topic_owner());
        return grpc::Status::OK;
    }
    Status communication_mom_to_mom::replicate_topic_subscription(::grpc::ServerContext* context, const ::mom_to_mom::topic_subscription* request, ::mom_to_mom::status* response){ 
        string topic_name = request->topic_name();
        string topic_owner = request->topic_owner();
        string queue_name = request->subscriber_queue_name();
        string queue_owner = request->subscriber_queue_owner();
        
        queue_obj* queue_to_subscribe = queues.get_specific_queue(queue_name, queue_owner);
        topic_obj* topic_to_subscribe = topics.get_specific_topic(topic_name, topic_owner);
        
        if(queue_to_subscribe != nullptr && topic_to_subscribe != nullptr) {
            topic_to_subscribe->subscribe_to_queue(*queue_to_subscribe);
            
            
            response->set_success(true);
            response->set_message("Subscription successful");
            return Status::OK;
        } else {
            response->set_success(false);
            response->set_message("Queue or topic not found");
            
            return Status(::grpc::StatusCode::NOT_FOUND, "Queue or topic not found");
        }
    }
    Status communication_mom_to_mom::replicate_topic_unsubscription(::grpc::ServerContext* context, const ::mom_to_mom::topic_subscription* request, ::mom_to_mom::status* response){ 
        string topic_name = request->topic_name();
        string topic_owner = request->topic_owner();
        string queue_name = request->subscriber_queue_name();
        string queue_owner = request->subscriber_queue_owner();
        
        queue_obj* queue_to_unsubscribe = queues.get_specific_queue(queue_name, queue_owner);
        topic_obj* topic_to_unsubscribe = topics.get_specific_topic(topic_name, topic_owner);
        
        if(queue_to_unsubscribe != nullptr && topic_to_unsubscribe != nullptr) {
            topic_to_unsubscribe->unsubscribe_from_queue(*queue_to_unsubscribe);
            
    
            
            response->set_success(true);
            response->set_message("Unsubscription successful");
            return Status::OK;
        } else {
            response->set_success(false);
            response->set_message("Queue or topic not found");
            
            return Status(::grpc::StatusCode::NOT_FOUND, "Queue or topic not found");
        }
    }

    Status communication_mom_to_mom::replicate_queue_message(::grpc::ServerContext* context, const ::mom_to_mom::structure_message* request, ::mom_to_mom::status* response) {
        std::string queue_name = request->structure_name();
        std::string content = request->content();
        std::string sender = request->sender();
        bool persistent = request->persistent();
        int64_t timestamp = request->timestamp();
    
        message new_message(queue_name, content, sender, persistent);
    
        queue_obj* found_queue = queues.get_specific_queue(queue_name, sender);
        if (found_queue != nullptr) {
            found_queue->add_message(new_message);
            response->set_success(true);
            response->set_message("Queue message replicated successfully");
            return Status::OK;
        }
    
        response->set_success(false);
        response->set_message("Queue not found");
        return Status(StatusCode::NOT_FOUND, "Queue not found");
    }
    
    Status communication_mom_to_mom::replicate_topic_message(::grpc::ServerContext* context, const ::mom_to_mom::structure_message* request, ::mom_to_mom::status* response) {
        std::string topic_name = request->structure_name();
        std::string content = request->content();
        std::string sender = request->sender();
        bool persistent = request->persistent();
        int64_t timestamp = request->timestamp();
    
        message new_message(topic_name, content, sender, persistent); 
    
        topic_obj* found_topic = topics.get_specific_topic(topic_name, sender);
        if (found_topic != nullptr) {
            for (queue_obj* q : found_topic->get_suscribers()) {
                q->add_message(new_message);
            }
            found_topic->increase_message_count();
            response->set_success(true);
            response->set_message("Topic message replicated successfully");
            return Status::OK;
        }
    
        response->set_success(false);
        response->set_message("Topic not found");
        return Status(StatusCode::NOT_FOUND, "Topic not found");
    }
    
    Status communication_mom_to_mom::replicate_receive_queue_message(::grpc::ServerContext* context, const ::mom_to_mom::queue_identifier* request, ::mom_to_mom::structure_message* response) {
        std::string queue_name = request->name();
        std::string queue_owner = request->owner();
    
        queue_obj* found_queue = queues.get_specific_queue(queue_name, queue_owner);
        if (found_queue != nullptr) {
            message* msg = found_queue->dequeue_message();
            if (msg != nullptr) {
                response->set_structure_name(msg->get_structure_name());
                response->set_content(msg->get_content());
                response->set_sender(msg->get_sender());
                response->set_timestamp(msg->get_creation_stamp());
                response->set_persistent(msg->is_persistent());
                return Status::OK;
            }
            return Status(StatusCode::NOT_FOUND, "No messages in queue");
        }
    
        return Status(StatusCode::NOT_FOUND, "Queue not found");
    }
    
    Status communication_mom_to_mom::replicate_receive_topic_message(::grpc::ServerContext* context, const ::mom_to_mom::topic_subscription* request, ::mom_to_mom::structure_message* response) {
        std::string topic_name = request->topic_name();
        std::string topic_owner = request->topic_owner();
    
        topic_obj* found_topic = topics.get_specific_topic(topic_name, topic_owner);
        if (found_topic != nullptr) {
            for (queue_obj* queue : found_topic->get_suscribers()) {
                message* msg = queue->dequeue_message();
                if (msg != nullptr) {
                    response->set_structure_name(msg->get_structure_name());
                    response->set_content(msg->get_content());
                    response->set_sender(msg->get_sender());
                    response->set_timestamp(msg->get_creation_stamp());
                    response->set_persistent(msg->is_persistent());
                    found_topic->decrease_message_count(); // mantener consistencia
                    return Status::OK;
                }
            }
            return Status(StatusCode::NOT_FOUND, "No messages in topic queues");
        }
    
        return Status(StatusCode::NOT_FOUND, "Topic not found");
    }
    




