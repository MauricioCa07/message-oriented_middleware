#include "crow.h"
#include <vector>
#include "rest_impl/rest_impl.h"
#include "node/node_impl.h"
using namespace std;
#include <thread>
#include <chrono>


vector<node_impl> nodes;


void create_nodes() {
    int num_nodes;
    cout << "How many nodes are you going to create ->";
    cin >> num_nodes;
    
    for (int i = 0; i < num_nodes; i++) { 
        string ip;
        int port;
        bool is_leader = (i == 0);
        
        cout << "ip -> ";
        cin >> ip;
        cout << "port-> ";
        cin >> port; 
        cout << "\n";
        
        nodes.emplace_back(node_impl(i, ip, port, is_leader));
        
        if(nodes[i].client->give_node_information(i, ip, port, is_leader)){
            std::cout<<"node "<<i<<" added correctly\n";
        }else{
            std::cout<<"node "<<i<<"couldnt be added\n";
        }
    }
}

void ping_nodes(){
    while(true){
        for(int i = 0;i<nodes.size();i++){
            if(!nodes[i].client->get_node_state()){
                nodes[i].set_alive(true);
            }else{
                nodes[i].set_alive(false);
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

}

void create_cluster(){
    for (int i = 0; i < nodes.size(); i++) { 
        for (int j = 0; j < nodes.size(); j++) {
            if (i != j){
                int n = nodes[j].get_id();
                std::string ip =  nodes[j].get_ip();
                int port = nodes[j].get_port();
                bool is_leader = nodes[j].is_leader();
                std::cout<<n<<" "<<ip<<" "<<port<<" "<<is_leader;
                nodes[i].client->give_cluster_information(n, ip, port, is_leader);
            }
        }
    }
}

int main(){
    create_nodes();
    create_cluster();
    std::thread nodes_state(ping_nodes);
    nodes_state.detach();


    crow::SimpleApp app; 


    
    /* --------------------------------------------------
       -                                                -
       -              ROUTES FOR AUTENTICATON           -
       -                                                -
       --------------------------------------------------
    */
    CROW_ROUTE(app, "/auth/login").methods("POST"_method)
    ([](const crow::request& req){
        return "Hello world";
    });


    CROW_ROUTE(app, "/auth/register").methods("POST"_method)
    ([](const crow::request& req){
        return "Hello world";
    });

    CROW_ROUTE(app, "/auth/logout`").methods("POST"_method)
    ([](const crow::request& req){
        return "Hello world";
    });



    /* ---------------------------------------------------
        -                                                -
        -           ROUTES FOR TOPICS MANAGEMENT         -
        -                                                -
        --------------------------------------------------
    */
    CROW_ROUTE(app, "/topics").methods("GET"_method,"POST"_method)
    ([](const crow::request& req){
        return nodes[0].client->list_topics();
    });

    CROW_ROUTE(app, "/topics/<string>").methods("POST"_method,"DELETE"_method)
    ([](const crow::request& req, const std::string& queue_name){
        auto url_params = crow::query_string(req.url_params);
        std::string owner;
    
        //We need the owner to know wich queue were goig to delete
        if (url_params.get("owner") != nullptr) {
            owner = url_params.get("owner");
        }else{
            return crow::response(400, "Missing 'owner' parameter");
        }

        //We see if the user want to create or delete
        //a queue, we do what the user want 👍
        if (req.method == crow::HTTPMethod::POST){
            if (nodes[0].client->create_topic(queue_name, owner)) {
                return crow::response(200, "Topic created successfully");
            }
        
            return crow::response(500, "Failed to create Topic");

        }if (req.method == crow::HTTPMethod::DELETE){
            
            if(nodes[0].client->delete_topic(queue_name,owner)){
                return crow::response(200, "Queue Topic successfully");
            }
            return crow::response(500, "Failed to Topic queue");
        }
    });



    /* ---------------------------------------------------
        -                                                -
        -           ROUTES FOR TOPICS QUEUES             -
        -                                                -
        --------------------------------------------------
    */
    CROW_ROUTE(app, "/queues").methods("GET"_method,"POST"_method)
    ([](const crow::request& req){
        return nodes[0].client->list_queues();
    });

    /*
        In this endpoint need the name of the new queue and
        also a param in the url called "owner" wich is used
        to createor delete a queue 
    */

    CROW_ROUTE(app, "/queues/<string>").methods("POST"_method,"DELETE"_method)
    ([](const crow::request& req, const std::string& queue_name){
        auto url_params = crow::query_string(req.url_params);
        std::string owner;
    
        //We need the owner to know wich queue were goig to delete
        if (url_params.get("owner") != nullptr) {
            owner = url_params.get("owner");
        }else{
            return crow::response(400, "Missing 'owner' parameter");
        }

        //We see if the user want to create or delete
        //a queue, we do what the user want 👍
        if (req.method == crow::HTTPMethod::POST){
            if (nodes[0].client->create_queue(queue_name, owner)) {
                return crow::response(200, "Queue created successfully");
            }
        
            return crow::response(500, "Failed to create queue");

        }if (req.method == crow::HTTPMethod::DELETE){
            
            if(nodes[0].client->delete_queue(queue_name,owner)){
                return crow::response(200, "Queue deleted successfully");
            }
            return crow::response(500, "Failed to delete queue");
        }
    });







    CROW_ROUTE(app, "/subscribe_queue").methods("POST"_method,"DELETE"_method)
    ([](const crow::request& req){
        auto url_params = crow::query_string(req.url_params);
        std::string topic_name,topic_owner,queue_name,queue_owner;
        //We need the owner to know wich queue were goig to delete
        if (!url_params.get("topic_name") || !url_params.get("topic_owner") ||
            !url_params.get("queue_name") || !url_params.get("queue_owner")) {
            return crow::response(400, "Missing parameters");
        }else{
                topic_name = url_params.get("topic_name");
                topic_owner = url_params.get("topic_owner");
                queue_name = url_params.get("queue_name");
                queue_owner  = url_params.get("queue_owner");
        }

        //We see if the user want to create or delete
        //a queue, we do what the user want 👍
        if (req.method == crow::HTTPMethod::POST){
            if (nodes[0].client->subscribe_topic(topic_name,topic_owner, queue_name,queue_owner)) {
                return crow::response(200, "The queue was successfully suscribed");
            }
        
            return crow::response(500, "Failed to create queue");

        }if (req.method == crow::HTTPMethod::DELETE){
            
            if(nodes[0].client->unsubscribe_topic(topic_name,topic_owner, queue_name,queue_owner)){
                return crow::response(200, "The queue was not suscribed");
            }
            return crow::response(500, "Failed to delete queue");
        }
    });


    /* ---------------------------------------------------
        -                                                -
        -           ROUTES FOR MESSAGES                  -
        -                                                -
        --------------------------------------------------
    */
   CROW_ROUTE(app, "/topics/<string>/message").methods("GET"_method, "POST"_method)
   ([&](const crow::request& req, const std::string& topic_name){
       auto url_params = crow::query_string(req.url_params);
       std::string owner, content;
   
       if (url_params.get("owner") != nullptr) {
           owner = url_params.get("owner");
       } else {
           return crow::response(400, "Missing 'owner' parameter");
       }
   
       if (req.method == crow::HTTPMethod::POST) {
           if (url_params.get("content") != nullptr) {
               content = url_params.get("content");
           } else {
               return crow::response(400, "Missing 'content' parameter");
           }
   
           if (nodes[0].client->send_topic_message(topic_name, content, owner)) {
               return crow::response(200, "The message was sent");
           }
           return crow::response(500, "Failed to send the message");
   
       } else if (req.method == crow::HTTPMethod::GET) {
           mom::structure_message result;
           if (nodes[0].client->request_topic_message(topic_name, owner, &result)) {
               return crow::response(200, result.content());
           }
           return crow::response(404, "No messages found in topic");
       }
   
       return crow::response(405, "Method Not Allowed");
   });
   

    
   CROW_ROUTE(app, "/queues/<string>/message").methods("GET"_method, "POST"_method)
([&](const crow::request& req, const std::string& queue_name){
    auto url_params = crow::query_string(req.url_params);
    std::string owner, content;

    if (url_params.get("owner") != nullptr) {
        owner = url_params.get("owner");
    } else {
        return crow::response(400, "Missing 'owner' parameter");
    }

    if (req.method == crow::HTTPMethod::POST) {
        if (url_params.get("content") != nullptr) {
            content = url_params.get("content");
        } else {
            return crow::response(400, "Missing 'content' parameter");
        }

        if (nodes[0].client->send_queue_message(queue_name, content, owner)) {
            return crow::response(200, "The message was sent to the queue");
        }
        return crow::response(500, "Failed to send the message");
        
    } else if (req.method == crow::HTTPMethod::GET) {
        mom::structure_message result;
        if (nodes[0].client->request_queue_message(queue_name, owner, &result)) {
            return crow::response(200, result.content());
        }
        return crow::response(404, "No messages found in queue");
    }

    return crow::response(405, "Method Not Allowed");
});





    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}
