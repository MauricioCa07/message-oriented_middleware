#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <sstream>

class MOMClient {
private:
    std::string base_url;

public:
    MOMClient(const std::string& url = "http://0.0.0.0:18080") 
        : base_url(url) {}

    // Topic management
    void list_topics() {
        cpr::Response res = cpr::Get(cpr::Url{base_url + "/topics"});
        std::cout << "Topics: " << res.text << std::endl;
    }

    void create_topic() {
        std::string topic_name, owner;
        std::cout << "Topic Name: ";
        std::cin >> topic_name;
        std::cout << "Owner: ";
        std::cin >> owner;
        
        cpr::Response res = cpr::Post(
            cpr::Url{base_url + "/topics/" + topic_name},
            cpr::Parameters{{"owner", owner}}
        );
        
        std::cout << "Response: " << res.status_code << " - " << res.text << std::endl;
    }

    void delete_topic() {
        std::string topic_name, owner;
        std::cout << "Topic Name: ";
        std::cin >> topic_name;
        std::cout << "Owner: ";
        std::cin >> owner;
        
        cpr::Response res = cpr::Delete(
            cpr::Url{base_url + "/topics/" + topic_name},
            cpr::Parameters{{"owner", owner}}
        );
        
        std::cout << "Response: " << res.status_code << " - " << res.text << std::endl;
    }

    // Queue management
    void list_queues() {
        cpr::Response res = cpr::Get(cpr::Url{base_url + "/queues"});
        std::cout << "Queues: " << res.text << std::endl;
    }

    void create_queue() {
        std::string queue_name, owner;
        std::cout << "Queue Name: ";
        std::cin >> queue_name;
        std::cout << "Owner: ";
        std::cin >> owner;
        
        cpr::Response res = cpr::Post(
            cpr::Url{base_url + "/queues/" + queue_name},
            cpr::Parameters{{"owner", owner}}
        );
        
        std::cout << "Response: " << res.status_code << " - " << res.text << std::endl;
    }

    void delete_queue() {
        std::string queue_name, owner;
        std::cout << "Queue Name: ";
        std::cin >> queue_name;
        std::cout << "Owner: ";
        std::cin >> owner;
        
        cpr::Response res = cpr::Delete(
            cpr::Url{base_url + "/queues/" + queue_name},
            cpr::Parameters{{"owner", owner}}
        );
        
        std::cout << "Response: " << res.status_code << " - " << res.text << std::endl;
    }

    // Subscription management
    void subscribe_queue() {
        std::string topic_name, topic_owner, queue_name, queue_owner;
        std::cout << "Topic: "; 
        std::cin >> topic_name;
        std::cout << "Topic owner: "; 
        std::cin >> topic_owner;
        std::cout << "Queue: "; 
        std::cin >> queue_name;
        std::cout << "Queue owner: ";
        std::cin >> queue_owner;
        
        cpr::Response res = cpr::Post(
            cpr::Url{base_url + "/subscribe_queue"},
            cpr::Parameters{
                {"topic_name", topic_name},
                {"topic_owner", topic_owner},
                {"queue_name", queue_name},
                {"queue_owner", queue_owner}
            }
        );
        
        std::cout << "Response: " << res.status_code << " - " << res.text << std::endl;
    }

    void unsubscribe_queue() {
        std::string topic_name, topic_owner, queue_name, queue_owner;
        std::cout << "Topic: "; 
        std::cin >> topic_name;
        std::cout << "Topic owner: "; 
        std::cin >> topic_owner;
        std::cout << "Queue: "; 
        std::cin >> queue_name;
        std::cout << "Queue owner: ";
        std::cin >> queue_owner;
        
        cpr::Response res = cpr::Delete(
            cpr::Url{base_url + "/subscribe_queue"},
            cpr::Parameters{
                {"topic_name", topic_name},
                {"topic_owner", topic_owner},
                {"queue_name", queue_name},
                {"queue_owner", queue_owner}
            }
        );
        
        std::cout << "Response: " << res.status_code << " - " << res.text << std::endl;
    }

    // Message handling
    void send_topic_message() {
        std::string topic_name, owner, message;
        std::cout << "Topic Name: ";
        std::cin >> topic_name;
        std::cout << "Owner: ";
        std::cin >> owner;
        std::cin.ignore(); // Clear newline from buffer
        std::cout << "Message content: ";
        std::getline(std::cin, message);
        
        cpr::Response res = cpr::Post(
            cpr::Url{base_url + "/topics/" + topic_name + "/message"},
            cpr::Parameters{
                {"owner", owner},
                {"content", message}
            }
        );
        
        std::cout << "Response: " << res.status_code << " - " << res.text << std::endl;
    }

    void receive_topic_message() {
        std::string topic_name, owner;
        std::cout << "Topic Name: ";
        std::cin >> topic_name;
        std::cout << "Owner: ";
        std::cin >> owner;
        
        cpr::Response res = cpr::Get(
            cpr::Url{base_url + "/topics/" + topic_name + "/message"},
            cpr::Parameters{{"owner", owner}}
        );
        
        std::cout << "Message: " << res.text << std::endl;
    }

    void send_queue_message() {
        std::string queue_name, owner, message;
        std::cout << "Queue Name: ";
        std::cin >> queue_name;
        std::cout << "Owner: ";
        std::cin >> owner;
        std::cin.ignore(); // Clear newline from buffer
        std::cout << "Message content: ";
        std::getline(std::cin, message);
        
        cpr::Response res = cpr::Post(
            cpr::Url{base_url + "/queues/" + queue_name + "/message"},
            cpr::Parameters{
                {"owner", owner},
                {"content", message}
            }
        );
        
        std::cout << "Response: " << res.status_code << " - " << res.text << std::endl;
    }

    void receive_queue_message() {
        std::string queue_name, owner;
        std::cout << "Queue Name: ";
        std::cin >> queue_name;
        std::cout << "Owner: ";
        std::cin >> owner;
        
        cpr::Response res = cpr::Get(
            cpr::Url{base_url + "/queues/" + queue_name + "/message"},
            cpr::Parameters{{"owner", owner}}
        );
        
        std::cout << "Message: " << res.text << std::endl;
    }

    void run_menu() {
        int option = 0;
        while (option != 11) {
            std::cout << "\n=== MENU MOM CLIENT ===\n";
            std::cout << "1. List topics\n";
            std::cout << "2. Create topic\n";
            std::cout << "3. Delete topic\n";
            std::cout << "4. List queues\n";
            std::cout << "5. Create queue\n";
            std::cout << "6. Delete queue\n";
            std::cout << "7. Subscribe queue to topic\n";
            std::cout << "8. Unsubscribe queue from topic\n";
            std::cout << "9. Send message to topic\n";
            std::cout << "10. Receive message from topic\n";
            std::cout << "11. Send message to queue\n";
            std::cout << "12. Receive message from queue\n";
            std::cout << "13. Quit\n";
            std::cout << "Option: ";
            std::cin >> option;

            switch (option) {
                case 1: list_topics(); break;
                case 2: create_topic(); break;
                case 3: delete_topic(); break;
                case 4: list_queues(); break;
                case 5: create_queue(); break;
                case 6: delete_queue(); break;
                case 7: subscribe_queue(); break;
                case 8: unsubscribe_queue(); break;
                case 9: send_topic_message(); break;
                case 10: receive_topic_message(); break;
                case 11: send_queue_message(); break;
                case 12: receive_queue_message(); break;
                case 13: 
                    std::cout << "Quitting...\n"; 
                    return;
                default: 
                    std::cout << "Invalid option\n";
            }
        }
    }
};

int main() {
    std::string server_url;
    std::cout << "Enter server URL (default: http://0.0.0.0:18080): ";
    std::getline(std::cin, server_url);
    
    if (server_url.empty()) {
        server_url = "http://172.18.0.4:18080";
    }
    
    MOMClient client(server_url);
    std::cout << "\n=== MOM CLIENT ===\n";
    client.run_menu();
    
    return 0;
}