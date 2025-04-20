#pragma once
#include "string"
#include "vector"
#include "../queue/queue_obj.h"
#include "map"

using namespace std;

class topic_obj{
    private:
        string topic_name;
        string topic_owner;
        time_t creation_stamp;
        vector<queue_obj*> subscribed_queues;
        int message_count;

    public:
    topic_obj(string topic_name,string topic_owner);
    
    topic_obj();
    /* ---------------------------------------------------
        -                                                -
        -                    GETTERS                     -
        -                                                -
        --------------------------------------------------
    */

    string get_topic_name();

    string get_topic_owner();

    time_t get_creation_stamp();

    vector<queue_obj*>& get_suscribers();

    
    int get_message_count();

    
    /* ---------------------------------------------------
        -                                                -
        -                    SETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    void set_topic_name(string new_name);

    void subscribe_to_queue(queue_obj& queue);

    void  set_topic_owner(std::string topic_owner);

    void  set_creation_stamp(time_t creation_stamp);

    void increase_message_count();

    void decrease_message_count();

    void unsubscribe_from_queue(queue_obj& queue);     
};






