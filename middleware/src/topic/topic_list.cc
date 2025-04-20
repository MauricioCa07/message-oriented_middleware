#include "topic_obj.h"
#include "topic_list.h"


int topic_list::add_topic_to_list(topic_obj topic){
    for(topic_obj topic_in_list:topic_list){
        if (topic_in_list.get_topic_name() == topic.get_topic_name()){
            cout<<"there is already a topic with this name"<<endl;
            return -1;
        }
    }
    this->topic_list.push_back(topic);
    return 0;
}



int topic_list::delete_topic_from_list(string topic_to_delete,string owner_topic_to_delete){
    for (int i = 0; i <= topic_list.size(); i++) {
        if (topic_list[i].get_topic_name() == topic_to_delete && topic_list[i].get_topic_owner() == owner_topic_to_delete ){
            this->topic_list.erase(topic_list.begin()+i);
            return 0;
        }
      }
    return -1;
}



vector<topic_obj> topic_list::get_topic_list(){return this->topic_list;}



topic_obj* topic_list::get_specific_topic(string name_topic_to_get, string owner_topic_to_get){
    for(topic_obj& topic_in_list:topic_list){ 
        if (topic_in_list.get_topic_name() == name_topic_to_get && topic_in_list.get_topic_owner() == owner_topic_to_get ){
            return &topic_in_list; 
        }
    }
    return nullptr;

}    



