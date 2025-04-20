#include "message.h"
#include "ctime"

message::message(string structure_name,string content,
    string sender,bool persistent){
        this->structure_name = structure_name;
        this->content = content;
        this->sender = sender;
        time_t now;
        time(&now);
        this->creation_stamp = now;
        this-> persistent = persistent;
}


string message::get_structure_name() const{return this->structure_name;}
string message::get_content() const{return this->content;}
string message::get_sender() const{return this->sender;}
int message::get_creation_stamp() const{return this->creation_stamp;}
bool message::is_persistent() const{return this->persistent;}

void message::set_creation_stamp(int creation_stamp){this->creation_stamp = creation_stamp;}