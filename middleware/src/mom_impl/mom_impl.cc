#include "mom_impl.h"
 

    /* ---------------------------------------------------
        -                                                -
        -              QUEUE'S METHODS                   -
        -                                                -
        --------------------------------------------------
    */

    /*
        Here we create the queue, then we see if there is a 
        queue with the same name in the queue_list and if so 
        we delete the object we just created. 
    */
   Status mom_impl::create_queue(::grpc::ServerContext* context, const ::mom::queue_config* request, ::mom::status* response) {
        string name = request->name();
        string owner = request->owner();

        queue_obj new_queue(name, owner);
        if(queues.add_queue_to_list(new_queue) == 0) {
            if (node_info->is_leader()) {
                for (auto& f : node_list) {
                    queue_obj new_queue;
                    grpc::ClientContext context;
                    std::string queue_name = new_queue.get_queue_name(); 
                    std::string queue_owner = new_queue.get_queue_owner();
                    mom_to_mom::queue replicate_request; 
    
                    
                    replicate_request.set_queue_name(queue_name); 
                    replicate_request.set_queue_owner(queue_owner); 
    
                    mom_to_mom::status replicate_response; 
                    auto status = f.client->replicate_queue(name, owner, &replicate_response);
                }
            }
            response->set_success(true);
            response->set_message("Queue added successfully");
            return ::grpc::Status::OK;
        }
        response->set_success(false);
        response->set_message("there was an error creating the queue");
        return Status(grpc::StatusCode::ABORTED,"");
    }


    /*
        In this method, we take the name of the queue and the 
        username. If the user is the one who created the queue,
        we simply delete the queue.
    */
   Status mom_impl::delete_queue(::grpc::ServerContext* context, const ::mom::queue_identifier* request, ::mom::status* response) {
    std::string queue_name = request->name();
    std::string queue_owner = request->owner();
    if (queues.delete_queue_from_list(queue_name, queue_owner) == 0) {
        if (node_info->is_leader()) {
            for (auto& f : node_list) {
                grpc::ClientContext context;

                mom_to_mom::status replicate_response; 
                auto status = f.client->replicate_delete_topic(queue_name, queue_owner, &replicate_response);
            }
        }
        response->set_success(true);
        response->set_message("Queue deleted successfully");
        return ::grpc::Status::OK;
    }
    response->set_success(false);
    response->set_message("This queue doesn't exits or you are not the owner");
    return Status(grpc::StatusCode::ABORTED,"");
    }   


    Status mom_impl::list_queues(::grpc::ServerContext* context, const ::mom::NodeID* request, ::mom::queues_response* response){
        std::vector<queue_obj> queues_list = queues.get_queue_list();

        for (queue_obj queue_to_return : queues_list) {
            mom::queue* queue_proto = response->add_queues();
    
            queue_proto->set_name(queue_to_return.get_queue_name());
            queue_proto->set_owner(queue_to_return.get_queue_owner());
            queue_proto->set_creation_timestamp(queue_to_return.get_creation_stamp());
            queue_proto->set_message_count(queue_to_return.get_message_count()); 
            
        }
        response->set_success(true);
        response->set_message("Queues listed successfully");
        return ::grpc::Status::OK;
    }


    Status mom_impl::get_queue_info(::grpc::ServerContext* context, const ::mom::queue_identifier* request, ::mom::queue* response){
        string queue_name = request->name();
        string queue_owner = request->owner();
    
        queue_obj* found_queue = queues.get_specific_queue(queue_name, queue_owner);
        if (found_queue != nullptr) {
            response->set_name(found_queue->get_queue_name());
            response->set_owner(found_queue->get_queue_owner());
            response->set_creation_timestamp(found_queue->get_creation_stamp());
            response->set_message_count(found_queue->get_message_count()); 
            return ::grpc::Status::OK;
        }
            return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "Queue not found");
    }
    
    
    

    
    /* ---------------------------------------------------
        -                                                -
        -              TOPIC'S METHODS                   -
        -                                                -
        --------------------------------------------------
    */


   Status mom_impl::create_topic(::grpc::ServerContext* context, const ::mom::topic_config* request, ::mom::status* response) {
    string name = request->name();
    string owner = request->owner();
    


    topic_obj new_topic(name, owner);
    if(topics.add_topic_to_list(new_topic) == 0) {
        if (node_info->is_leader()) {
            for (auto& f : node_list) {
                grpc::ClientContext context;
                std::string topic_name = new_topic.get_topic_name(); 
                std::string topic_owner = new_topic.get_topic_owner();
                mom_to_mom::topic replicate_request; 

                
                replicate_request.set_topic_name(topic_name); 
                replicate_request.set_topic_owner(topic_owner); 

                mom_to_mom::status replicate_response; 
                auto status = f.client->replicate_topic(name, owner, &replicate_response);
            }
        }
        response->set_success(true);
        response->set_message("topic added successfully");
        return ::grpc::Status::OK;

    }
    response->set_success(false);
    response->set_message("there was an error creating the topic");
    return Status(grpc::StatusCode::ABORTED,"");

   }



Status mom_impl::delete_topic(::grpc::ServerContext* context, const ::mom::topic_identifier* request, ::mom::status* response) {
    std::string topic_name = request->name();
    std::string topic_owner = request->owner();
    if (topics.delete_topic_from_list(topic_name, topic_owner) == 0) {
            for (auto& f : node_list) {
                grpc::ClientContext context;
                mom_to_mom::status replicate_response; 
                auto status = f.client->replicate_delete_topic(topic_name, topic_owner, &replicate_response);
            }
        response->set_success(true);
        response->set_message("topic deleted successfully");
        return ::grpc::Status::OK;
    }
    response->set_success(false);
    response->set_message("This topic doesn't exits or you are not the owner");
    return Status(grpc::StatusCode::ABORTED,"");
    }
    
    Status mom_impl::list_topics(::grpc::ServerContext* context, const ::mom::NodeID* request, ::mom::topics_response* response)  {
    std::vector<topic_obj> topics_list = topics.get_topic_list();
    for (topic_obj topic_to_return : topics_list) {
        mom::topic* topic_proto = response->add_topics();
        topic_proto->set_name(topic_to_return.get_topic_name());
        topic_proto->set_owner(topic_to_return.get_topic_owner());
        topic_proto->set_creation_timestamp(topic_to_return.get_creation_stamp());
        topic_proto->set_message_count(topic_to_return.get_message_count());

        vector<queue_obj*> subscribers = topic_to_return.get_suscribers();
        if(subscribers.size() > 0) {
            for (queue_obj* subscribed_queue : subscribers) {
                mom::queue* queue_proto = topic_proto->add_subscribers();
                
                queue_proto->set_name(subscribed_queue->get_queue_name());
                queue_proto->set_owner(subscribed_queue->get_queue_owner());
                queue_proto->set_creation_timestamp(subscribed_queue->get_creation_stamp());
                queue_proto->set_message_count(subscribed_queue->get_message_count());
            }
        }
        
        topic_proto->set_message_count(topic_to_return.get_message_count());
    }
    
    response->set_success(true);
    response->set_message("topics listed successfully");
    return ::grpc::Status::OK;
}


Status mom_impl::get_topic_info(::grpc::ServerContext* context, const ::mom::topic_identifier* request, ::mom::topic* response)  {
    string topic_name = request->name();
    string topic_owner = request->owner();


    topic_obj* found_topic = topics.get_specific_topic(topic_name, topic_owner);

    if (found_topic != nullptr) {
        response->set_name(found_topic->get_topic_name());
        response->set_owner(found_topic->get_topic_owner());
        response->set_creation_timestamp(found_topic->get_creation_stamp());
        response->set_message_count(found_topic->get_message_count());
        

        vector<queue_obj*> subscribers = found_topic->get_suscribers();
        for (queue_obj* subscribed_queue : subscribers) {
            mom::queue* queue_proto = response->add_subscribers();
            queue_proto->set_name(subscribed_queue->get_queue_name());
            queue_proto->set_owner(subscribed_queue->get_queue_owner());
            queue_proto->set_creation_timestamp(subscribed_queue->get_creation_stamp());
            queue_proto->set_message_count(subscribed_queue->get_message_count());
        }
        
        return ::grpc::Status::OK;
    }

    return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "topic not found");
}
    
    
    
    
Status mom_impl::subscribe_topic(::grpc::ServerContext* context, const ::mom::topic_subscription* request, ::mom::status* response) {
    string topic_name = request->topic_name();
    string topic_owner = request->topic_owner();
    string queue_name = request->subscriber_queue_name();
    string queue_owner = request->subscriber_queue_owner();
    
    queue_obj* queue_to_subscribe = queues.get_specific_queue(queue_name, queue_owner);
    topic_obj* topic_to_subscribe = topics.get_specific_topic(topic_name, topic_owner);
    
    if(queue_to_subscribe != nullptr && topic_to_subscribe != nullptr) {
        topic_to_subscribe->subscribe_to_queue(*queue_to_subscribe);
        if (node_info->is_leader()) {
            for (auto& f : node_list) {
                grpc::ClientContext context;
                mom_to_mom::status replicate_response; 
                auto status = f.client->replicate_topic_subscription(topic_name, topic_owner,queue_name,queue_owner, &replicate_response);
            }
        
        
                response->set_success(true);
                response->set_message("Subscription successful");
                return Status::OK;
        }
    }else {
        response->set_success(false);
        response->set_message("Queue or topic not found");
        
        return Status(::grpc::StatusCode::NOT_FOUND, "Queue or topic not found");
    }
}


Status mom_impl::unsubscribe_topic(::grpc::ServerContext* context, const ::mom::topic_subscription* request, ::mom::status* response) {
    string topic_name = request->topic_name();
    string topic_owner = request->topic_owner();
    string queue_name = request->subscriber_queue_name();
    string queue_owner = request->subscriber_queue_owner();
    
    queue_obj* queue_to_unsubscribe = queues.get_specific_queue(queue_name, queue_owner);
    topic_obj* topic_to_unsubscribe = topics.get_specific_topic(topic_name, topic_owner);
    
    if(queue_to_unsubscribe != nullptr && topic_to_unsubscribe != nullptr) {
        topic_to_unsubscribe->unsubscribe_from_queue(*queue_to_unsubscribe);
        for (auto& f : node_list) {
            grpc::ClientContext context;
            mom_to_mom::status replicate_response; 
            auto status = f.client->replicate_topic_unsubscription(topic_name, topic_owner,queue_name,queue_owner, &replicate_response);
        }

        
        response->set_success(true);
        response->set_message("Unsubscription successful");
        return Status::OK;
    } else {
        response->set_success(false);
        response->set_message("Queue or topic not found");
        
        return Status(::grpc::StatusCode::NOT_FOUND, "Queue or topic not found");
    }
}
  
    
    
    
    
    /* ---------------------------------------------------
        -                                                -
        -                     MESSAGES                   -
        -                                                -
        -------------------------------------------------- 
    */
   Status mom_impl::send_queue_message(::grpc::ServerContext* context, const ::mom::structure_message* request, ::mom::message_status* response){
    string queue_name = request->structure_name();
    string content = request->content();
    string queue_owner = request->sender();
    bool persistent = request->persistent();
    int64_t timestamp = std::time(nullptr);

    message new_message(queue_name, content, queue_owner, persistent);
    new_message.set_creation_stamp(timestamp);

    queue_obj* found_queue = queues.get_specific_queue(queue_name, queue_owner);
    if (found_queue != nullptr) {
        found_queue->add_message(new_message);

        if (node_info->is_leader()) {
            for (auto& f : node_list) {
                mom_to_mom::status replicate_response;
                f.client->replicate_queue_message(queue_name, content, queue_owner, timestamp, persistent, &replicate_response);
            }
        }

        response->set_success(true);
        response->set_message("Message added successfully");
        return ::grpc::Status::OK;
    }

    response->set_success(false);
    response->set_message("Message could not be delivered");
    return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "Queue not found");
    }

    
    Status mom_impl::receive_queue_message(::grpc::ServerContext* context, const ::mom::queue_identifier* request, ::mom::structure_message* response){
        string queue_name = request->name();
        string queue_owner = request->owner();
    
        queue_obj* found_queue = queues.get_specific_queue(queue_name, queue_owner);
        if (found_queue != nullptr) {
            message* msg = found_queue->dequeue_message();
            if (msg != nullptr){
                response->set_structure_name(msg->get_structure_name());
                response->set_content(msg->get_content());
                response->set_sender(msg->get_sender());
                response->set_timestamp(msg->get_creation_stamp());
                response->set_persistent(msg->is_persistent());
    
                if (node_info->is_leader()) {
                    for (auto& f : node_list) {
                        mom_to_mom::structure_message dummy;
                        f.client->replicate_receive_queue_message(queue_name, queue_owner, &dummy);
                    }
                }
    
                return ::grpc::Status::OK;
            }
            return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "No messages in queue"); 
        }
    
        return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "Queue not found");    
    }
    
    
    Status mom_impl::publish_topic_message(::grpc::ServerContext* context, const ::mom::structure_message* request, ::mom::message_status* response){
        string topic_name = request->structure_name();
        string content = request->content();
        string topic_owner = request->sender();
        bool persistent = request->persistent();
        int64_t timestamp = std::time(nullptr);
    
        message new_message(topic_name, content, topic_owner, persistent);
        new_message.set_creation_stamp(timestamp);
    
        topic_obj* found_topic = topics.get_specific_topic(topic_name, topic_owner);
        if (found_topic != nullptr) {
            for (queue_obj* q : found_topic->get_suscribers()) {
                q->add_message(new_message);
            }
            found_topic->increase_message_count();
    
            if (node_info->is_leader()) {
                for (auto& f : node_list) {
                    mom_to_mom::status replicate_response;
                    f.client->replicate_topic_message(topic_name, content, topic_owner, timestamp, persistent, &replicate_response);
                }
            }
    
            response->set_success(true);
            response->set_message("Message added successfully");
            return ::grpc::Status::OK;
        }
    
        response->set_success(false);
        response->set_message("Message could not be delivered");
        return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "Topic not found");
    }
    
    
    Status mom_impl::receive_topic_message(::grpc::ServerContext* context, const ::mom::topic_subscription* request, ::mom::structure_message* response){
        string topic_name = request->topic_name();
        string topic_owner = request->topic_owner();
    
        topic_obj* found_topic = topics.get_specific_topic(topic_name, topic_owner);
        if (found_topic != nullptr) {
            for (queue_obj* queue_subscribed : found_topic->get_suscribers()) {
                message* msg = queue_subscribed->dequeue_message();
                if (msg != nullptr) {
                    response->set_structure_name(msg->get_structure_name()); 
                    response->set_content(msg->get_content());
                    response->set_sender(msg->get_sender());
                    response->set_timestamp(msg->get_creation_stamp());
                    response->set_persistent(msg->is_persistent());
    
                    if (node_info->is_leader()) {
                        for (auto& f : node_list) {
                            mom_to_mom::structure_message dummy;
                            f.client->replicate_receive_topic_message(topic_name, topic_owner, queue_subscribed->get_queue_name(), queue_subscribed->get_queue_owner(), true, &dummy);
                        }
                    }
    
                    found_topic->decrease_message_count();            
                    return ::grpc::Status::OK;
                }
            }
        }
    
        return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "Topic not found");
    }
    
    
    Status mom_impl::acknowledge_message(::grpc::ServerContext* context, const ::mom::message_identifier* request, ::mom::status* response){return Status::OK;}
    /* ---------------------------------------------------
        -                                                -
        -                     CLUSTER                    -
        -                                                -
        --------------------------------------------------
    */
   Status mom_impl::join_cluster(::grpc::ServerContext* context, const ::mom::node_info* request, ::mom::status* response){
        node_info = node_impl(
            request->node_id(),
            request->ip(),
            request->port(),
            request->leader()
        );

        response->set_success(true);
        response->set_message("node joined to the cluster");

        return Status::OK;
    }

    Status mom_impl::leave_cluster(::grpc::ServerContext* context, const ::mom::NodeID* request, ::mom::status* response){return Status::OK;}
    Status mom_impl::heartbeat(::grpc::ServerContext* context, const ::mom::NodeID* request, ::mom::status* response){return Status::OK;}
    Status mom_impl::get_node_state(::grpc::ServerContext* context, const ::mom::node_status* request, ::mom::node_status* response){
        response->set_active(true);
        return Status::OK;
    }

    Status mom_impl::set_cluster(::grpc::ServerContext* context, const ::mom::node_info* request, ::mom::status* response){
        int id = request->node_id();
        std::string ip = request->ip();
        int port = request->port();
        bool leader = request->leader();
        
        std::cout<<id<<" "<<ip<<" "<<port<<" "<<leader;
        this->node_list.emplace_back(id,ip,port,leader);
        

        response->set_success(true);
        response->set_message("node joined to the cluster");

        return Status::OK;
    
    }

    queue_list& mom_impl::get_queues(){ return queues; }
    topic_list& mom_impl::
get_topics(){ return topics; }
