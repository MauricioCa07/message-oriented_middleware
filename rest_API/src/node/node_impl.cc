#include "node_impl.h"

node_impl::node_impl(const int& id, const std::string& ip, int port, bool is_leader) {
    this->id = id;
    this->ip = ip;
    this->port = port;
    this->leader = is_leader;
    auto channel = grpc::CreateChannel(ip + ":" + std::to_string(port), grpc::InsecureChannelCredentials());
    this->client = std::make_unique<rest_impl>(channel);
};

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
