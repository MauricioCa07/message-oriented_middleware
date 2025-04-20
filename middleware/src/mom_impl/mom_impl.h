#pragma once
#include <grpcpp/grpcpp.h>
#include "../../protos/api_rest/mom.pb.h"
#include "../../protos/api_rest/mom.grpc.pb.h"

#include "../../protos/mom_to_mom/mom_to_mom.pb.h"
#include "../../protos/api_rest/mom.grpc.pb.h"

#include "../topic/topic_list.h"
#include "../queue/queue_list.h"


#include "../queue/queue_obj.h"
#include "../topic/topic_obj.h"

#include "../message/message.h"

#include "../node/node_impl.h"

#include "../mom_to_mom/communication_mom_to_mom.h"

#include <ctime>
#include <string>


using grpc::ServerContext;
using grpc::Status;
using grpc::ServerBuilder;
using grpc::Server;





class mom_impl final : public mom::MOM_service::Service {
    private:
        queue_list queues;
        topic_list topics;
        std::optional<node_impl> node_info;
        vector<node_impl> node_list;

        bool is_leader;

        void replicate_to_followers(const std::function<Status(node_impl&, grpc::ClientContext&)>& operation);
    
        bool should_replicate() const {
            return is_leader && !node_list.empty();
        }
        
    public:
        /*
          Here we create the queue, then we see if there is a 
          queue with the same name in the queue_list and if so 
          we delete the object we just created. 
        */
        Status create_queue(::grpc::ServerContext* context, const ::mom::queue_config* request, ::mom::status* response)override;
  
  
        /*
          In this method, we take the name of the queue and the 
          username. If the user is the one who created the queue,
           we simply delete the queue.
        */
        Status delete_queue(::grpc::ServerContext* context, const ::mom::queue_identifier* request, ::mom::status* response)override;
  
  
        Status list_queues(::grpc::ServerContext* context, const ::mom::NodeID* request, ::mom::queues_response* response)override;
  
   
        Status get_queue_info(::grpc::ServerContext* context, const ::mom::queue_identifier* request, ::mom::queue* response)override;
        
        
        
        
        
      /* ---------------------------------------------------
          -                                                -
          -              TOPIC'S METHODS                   -
          -                                                -
          --------------------------------------------------
      */
        Status create_topic(::grpc::ServerContext* context, const ::mom::topic_config* request, ::mom::status* response)override;
  
  
  
  
        Status delete_topic(::grpc::ServerContext* context, const ::mom::topic_identifier* request, ::mom::status* response)override;
        
        
        
        Status list_topics(::grpc::ServerContext* context, const ::mom::NodeID* request, ::mom::topics_response* response)override;
              
        
        
        Status get_topic_info(::grpc::ServerContext* context, const ::mom::topic_identifier* request, ::mom::topic* response)override;
        
        
        
        
        Status subscribe_topic(::grpc::ServerContext* context, const ::mom::topic_subscription* request, ::mom::status* response)override;
    
  
        Status unsubscribe_topic(::grpc::ServerContext* context, const ::mom::topic_subscription* request, ::mom::status* response)override;
      
        
        
        
        
        
        
      /* ---------------------------------------------------
          -                                                -
          -                     MESSAGES                   -
          -                                                -
          -------------------------------------------------- 
      */
        Status send_queue_message(::grpc::ServerContext* context, const ::mom::structure_message* request, ::mom::message_status* response)override;
        Status receive_queue_message(::grpc::ServerContext* context, const ::mom::queue_identifier* request, ::mom::structure_message* response)override;
        Status publish_topic_message(::grpc::ServerContext* context, const ::mom::structure_message* request, ::mom::message_status* response)override;
        Status receive_topic_message(::grpc::ServerContext* context, const ::mom::topic_subscription* request, ::mom::structure_message* response)override;
        Status acknowledge_message(::grpc::ServerContext* context, const ::mom::message_identifier* request, ::mom::status* response)override;
        /* ---------------------------------------------------
          -                                                -
          -                     CLUSTER                    -
          -                                                -
          --------------------------------------------------
      */
        Status join_cluster(::grpc::ServerContext* context, const ::mom::node_info* request, ::mom::status* response)override;
        Status leave_cluster(::grpc::ServerContext* context, const ::mom::NodeID* request, ::mom::status* response)override;
        Status heartbeat(::grpc::ServerContext* context, const ::mom::NodeID* request, ::mom::status* response)override;
        Status get_node_state(::grpc::ServerContext* context, const ::mom::node_status* request, ::mom::node_status* response)override;
        Status set_cluster(::grpc::ServerContext* context, const ::mom::node_info* request, ::mom::status* response)override;




        queue_list& get_queues();       
        topic_list& get_topics();
};