#include "node_impl.h"




node_impl::node_impl(const int& id, const std::string& ip, int port, bool is_leader)
    : id(id), ip(ip), port(port), leader(is_leader), alive(true) {
    
    auto channel = grpc::CreateChannel(ip + ":" + std::to_string(port), grpc::InsecureChannelCredentials());
    client = std::make_unique<communication_mom_stub>(channel);
}

int node_impl::get_id(){return this->id;}      
std::string node_impl::get_ip(){return this->ip;}   
int node_impl::get_port(){return this->port;}
bool node_impl::is_leader(){return this->leader;}
bool node_impl::is_alive(){return this->alive;}



void node_impl::set_id(int id){this->id = id;}
void node_impl::set_ip(std::string ip){this->ip = ip;}
void node_impl::set_port(int port){this->port = port;}
void node_impl::set_leader(bool leader){this->leader = leader;}
void node_impl::set_alive(bool alive){this->alive = alive;}

