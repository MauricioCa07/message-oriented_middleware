#pragma once
#include <string>
#include <grpcpp/grpcpp.h>
#include "../rest_impl/rest_impl.h"
#include <vector>
#include <memory>

class rest_impl;

class node_impl{
    private: 
        int id;
        std::string ip;
        int port;
        bool leader;
        bool alive;
        

    public: 

    std::unique_ptr<rest_impl> client;
    node_impl(const int& id, const std::string& ip, int port, bool leader);

    int get_id();    
    std::string get_ip();    
    int get_port();
    bool is_leader();
    bool is_alive();

    void set_id(int id);    
    void set_ip(std::string ip);
    void set_port(int port);
    void set_leader(bool leader);
    void set_alive(bool alive);

   
};

