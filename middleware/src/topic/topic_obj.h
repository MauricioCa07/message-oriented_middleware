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
        vector<queue_obj>  subscribed_topics;
        int message_count;
        map<string, string> properties;

    public:
    topic_obj(string topic_name,string topic_owner, map<string, string> properties);
    
    /* ---------------------------------------------------
        -                                                -
        -                    GETTERS                     -
        -                                                -
        --------------------------------------------------
    */

    string get_topic_name();

    string get_topic_owner();

    time_t get_creation_stamp();

    map<string,string> get_properties();
    
    int get_message_count();

    
    /* ---------------------------------------------------
        -                                                -
        -                    SETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    void set_topic_name(string new_name);

    void set_properties(map<string,string> new_properties);



    void subscribe_to_queue(queue_obj& queue);


    void unsubscribe_from_queue(queue_obj& queue);     
};






