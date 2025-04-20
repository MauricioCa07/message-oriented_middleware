#pragma once
#include <string>
#include <memory>
#include "../mom_to_mom/communication_mom_stub.h"  // ⬅️ Incluye tu cliente real

class node_impl {
private:
    int id;
    std::string ip;
    int port;
    bool leader;
    bool alive;

public:
    std::unique_ptr<communication_mom_stub> client;

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
