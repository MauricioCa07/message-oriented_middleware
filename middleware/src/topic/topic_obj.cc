#include  "topic_obj.h"

    topic_obj::topic_obj(string topic_name,string topic_owner){
        this->topic_name = topic_name;
        this->topic_owner = topic_owner;
        time_t now;
        time(&now);
        this->creation_stamp = now;
        this->message_count = 0;
    };

    topic_obj::topic_obj(){}

    /* ---------------------------------------------------
        -                                                -
        -                    GETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    string topic_obj::get_topic_name() {return this->topic_name;}

    string topic_obj::get_topic_owner() {return this->topic_owner;}

    time_t topic_obj::get_creation_stamp() {return this->creation_stamp;}

    vector<queue_obj*>& topic_obj::get_suscribers() {
        return this->subscribed_queues;
    }

    int topic_obj::get_message_count(){return this->message_count;}

    



   /* ---------------------------------------------------
        -                                                -
        -                    SETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    void topic_obj::set_topic_name(string new_name){this->topic_name =new_name;}

    void topic_obj::subscribe_to_queue(queue_obj& queue) {
        for (queue_obj* q : this->subscribed_queues) {
            if (q == &queue) {
                return;
            }
        }
        subscribed_queues.push_back(&queue);
    }
    

    void topic_obj::set_topic_owner(std::string topic_owner){
        this->topic_owner = topic_owner;
    }

    void  topic_obj::set_creation_stamp(time_t creation_stamp){
        this->creation_stamp = creation_stamp;
    }


    void topic_obj::increase_message_count(){
        this->message_count += 1;
    }

    void topic_obj::decrease_message_count(){
        this->message_count -= 1;
    }
    

    void topic_obj::unsubscribe_from_queue(queue_obj& queue){
        for (int i = 0; i < this->subscribed_queues.size(); i++) {
            if (this->subscribed_queues[i] == &queue){
                this->subscribed_queues.erase(this->subscribed_queues.begin()+i);
            }
        }
        return ;
    }

    










