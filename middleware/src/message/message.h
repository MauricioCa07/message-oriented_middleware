#pragma once
#include "string"

using namespace std;

class message{
private:
    string structure_name;
    string content;
    string sender;
    int creation_stamp;
    bool persistent;  

    public:
    message(string structure_name,string content,
        string sender,bool persistent);


    string get_structure_name() const;
    string get_content() const;
    string get_sender() const;
    int get_creation_stamp() const;
    bool is_persistent() const;

    void set_creation_stamp(int creation_stamp);
};





