#pragma once
#include "topic_obj.h"
#include "string"
#include "vector"


using namespace std;

class topic_list{
    private:
    vector<topic_obj> topic_list;

    public:
    int add_topic_to_list(topic_obj topic);

    int delete_topic_from_list(string topic_to_delete,string owner_topic_to_delete);

    vector<topic_obj> get_topic_list();
    
    topic_obj* get_specific_topic(string name_topic_to_get, string owner_topic_to_get);
};