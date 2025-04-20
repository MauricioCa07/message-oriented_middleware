// communication_mom_to_mom.h
#pragma once
#include <grpcpp/grpcpp.h>
#include "../../protos/mom_to_mom/mom_to_mom.grpc.pb.h"

#include "../queue/queue_list.h"
#include "../topic/topic_list.h"


#include "../topic/topic_obj.h"
#include "../queue/queue_obj.h"

#include "../message/message.h"

using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;
using grpc::ServerBuilder;
using grpc::Server;


class communication_mom_to_mom : public  mom_to_mom::MOM_cluster_service::Service{
    private:
        queue_list& queues;
        topic_list& topics;
    public: 
    communication_mom_to_mom(queue_list& queues_ref, topic_list& topics_ref)
        : queues(queues_ref), topics(topics_ref) {}

        Status replicate_topic(::grpc::ServerContext* context, const ::mom_to_mom::topic* request, ::mom_to_mom::status* response)override;
        Status replicate_queue(::grpc::ServerContext* context, const ::mom_to_mom::queue* request, ::mom_to_mom::status* response)override;
        Status replicate_delete_queue(::grpc::ServerContext* context, const ::mom_to_mom::queue* request, ::mom_to_mom::status* response)override;
        Status replicate_delete_topic(::grpc::ServerContext* context, const ::mom_to_mom::topic* request, ::mom_to_mom::status* response)override;
        Status replicate_topic_subscription(::grpc::ServerContext* context, const ::mom_to_mom::topic_subscription* request, ::mom_to_mom::status* response)override;
        Status replicate_topic_unsubscription(::grpc::ServerContext* context, const ::mom_to_mom::topic_subscription* request, ::mom_to_mom::status* response)override;
        Status replicate_queue_message(::grpc::ServerContext* context, const ::mom_to_mom::structure_message* request, ::mom_to_mom::status* response)override;
        Status replicate_topic_message(::grpc::ServerContext* context, const ::mom_to_mom::structure_message* request, ::mom_to_mom::status* response)override;
        Status replicate_receive_queue_message(::grpc::ServerContext* context, const ::mom_to_mom::queue_identifier* request, ::mom_to_mom::structure_message* response)override;
        Status replicate_receive_topic_message(::grpc::ServerContext* context, const ::mom_to_mom::topic_subscription* request, ::mom_to_mom::structure_message* response)override;

};