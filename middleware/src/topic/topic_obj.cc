#include  "topic_obj.h"

    topic_obj::topic_obj(string topic_name,string topic_owner, map<string, string> properties){
        this->topic_name = topic_name;
        this->topic_owner = topic_owner;
        time_t now;
        time(&now);
        this->creation_stamp = now;
        this->message_count = 0;
        this->properties = properties;
    };




    /* ---------------------------------------------------
        -                                                -
        -                    GETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    string topic_obj::get_topic_name() {return this->topic_name;}

    string topic_obj::get_topic_owner() {return this->topic_owner;}

    time_t topic_obj::get_creation_stamp() {return this->creation_stamp;}

    map<string,string> topic_obj::get_properties(){return this->properties;}

    int topic_obj::get_message_count(){return this->message_count;}





   /* ---------------------------------------------------
        -                                                -
        -                    SETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    void topic_obj::set_topic_name(string new_name){this->topic_name =new_name;}

    void topic_obj::set_properties(map<string,string> new_properties){this->properties = new_properties;}



    void topic_obj::subscribe_to_queue(queue_obj &queue){
        this->subscribed_topics.push_back(queue);
    }


    void topic_obj::unsubscribe_from_queue(queue_obj& queue){
        for (int i = 0; i < this->subscribed_topics.size(); i++) {
            if (this->subscribed_topics[i] ==  queue){
                this->subscribed_topics.erase(this->subscribed_topics.begin()+i);
            }
        }
    }










