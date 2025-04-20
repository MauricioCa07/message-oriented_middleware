#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <ctime>
#include <map>
#include "../message/message.h"

using namespace std;

class queue_obj {
private:
    string queue_name;
    string queue_owner;
    time_t creation_stamp;
    std::queue<message> message_queue;

public:
    queue_obj(string name, string owner);

    queue_obj();
    /* ---------------------------------------------------
        -                                                -
        -                    GETTERS                     -
        -                                                -
        --------------------------------------------------
    */

    string get_queue_name() const;

    string get_queue_owner() const;

    time_t get_creation_stamp() const;
    
    int get_message_count() const;

    
    /* ---------------------------------------------------
        -                                                -
        -                    SETTERS                     -
        -                                                -
        --------------------------------------------------
    */
    void set_queue_name(string new_name);

    void set_queue_owner(string new_owner);
    
    void set_creation_stamp(time_t creation_stamp);

    void add_message(message message);

    message* dequeue_message();

    bool operator== (queue_obj& queue_to_compare);   
};
