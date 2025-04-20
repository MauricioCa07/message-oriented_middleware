#include "queue_obj.h"

    queue_obj::queue_obj(string name, string owner) {
        this->queue_name = name;
        this->queue_owner = owner;
        time_t now;
        time(&now);
        this->creation_stamp = now;
    }

    queue_obj::queue_obj(){

    }




    /* ---------------------------------------------------
        -                                                -
        -                    GETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    string queue_obj::get_queue_name() const {return this->queue_name;}

    string queue_obj::get_queue_owner() const {return this->queue_owner;}

    time_t queue_obj::get_creation_stamp() const {return this->creation_stamp;}

    int queue_obj::get_message_count() const {return message_queue.size();}





   /* ---------------------------------------------------
        -                                                -
        -                    SETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    void queue_obj::set_queue_name(string new_name){this->queue_name =new_name;}


    void  queue_obj::set_queue_owner(string new_owner){this->queue_owner=new_owner;}

    void queue_obj::set_creation_stamp(time_t creation_stamp){this->creation_stamp = creation_stamp;}


    void queue_obj::add_message(message message) {
        this->message_queue.push(message);
    }

    message* queue_obj::dequeue_message() {
        if (this->message_queue.empty()) {
            return nullptr;
        } else {
            message front_message_copy = this->message_queue.front(); 
    
            
            this->message_queue.pop();
            message* heap_message = new message(std::move(front_message_copy));
    
            return heap_message;
        }
    }

    bool queue_obj::operator==(queue_obj& queue_to_compare){
        return this->queue_name == queue_to_compare.get_queue_name()  && 
            this->queue_owner == queue_to_compare.get_queue_owner() && 
            this->creation_stamp == queue_to_compare.get_creation_stamp();
    }




    