# MESSAGES ORIENTED MIDDLEWARE

In this poject we're presenting an entire architecture with an API rest, a cluster of MOM's and some clients. 

The idea is that the clients will
- create and delete topics 
- create and delete queues
- create and delete messages inside each structure

## How to run the project 
### API REST

**UNIX** Go inside `rest_API` and run the following command
```console 
    rm -rf build/;mkdir build; cd build; cmake ..;make;./mom
```

**WINDOWS** Go inside `rest_API` and run the following command
```console 
    Remove-Item -Recurse -Force build; New-Item -ItemType Directory -Path build; Set-Location -Path build; cmake ..; make; ./mom
```
After this your endpoints should be running


### MOM


**UNIX** Go inside `mom_communication` and run the following command
```console 
    rm -rf build/;mkdir build; cd build; cmake ..;make
```

**WINDOWS** Go inside `rest_API` and run the following command
```console 
    Remove-Item -Recurse -Force build; New-Item -ItemType Directory -Path build; Set-Location -Path build; cmake ..; make; ./mom
```
> you should clone, compile and link the grpc library, for this project we used the v1.71.0

## Related links 
- **Build gRPC with Cmake** - https://github.com/grpc/grpc/blob/v1.71.0/BUILDING.md

- **Download crow** - https://crowcpp.org/master/getting_started/setup/linux/

- **gRPC DOCS** - https://grpc.io/docs/languages/cpp/basics/

## Project Description
This project involves the design and implementation of a Message-Oriented Middleware (MOM) that enables asynchronous communication between multiple client applications through queues and topics. The system is designed with a cluster approach, allowing for multiple MOM nodes that ensure high availability and fault tolerance.
The middleware abstracts the complexity of communication between applications, allowing clients to focus on their business logic rather than worrying about the details of communication in distributed systems.

### Key Features
- Cluster Architecture: Distributed system with multiple nodes working together to ensure high availability.
- Leader-Follower Mechanism: A leader node coordinates operations and replicates data to follower nodes.
- Topic Management: Create, delete, and list topics for publish-subscribe messaging patterns.
- Queue Management: Create, delete, and list queues for point-to-point messaging.
- Authentication: User authentication for secure connections.
- Message Persistence: Option to persist messages for durability.
- Fault Tolerance: Mechanisms to handle node failures and ensure system reliability.
- REST API: Client-facing API for easy integration.
- gRPC Communication: Efficient node-to-node communication using gRPC.
- Topic Subscription: Clients can subscribe queues to topics to receive messages.

### Technologies Used

- C++: Core implementation language
- gRPC: For efficient node-to-node communication
- Protocol Buffers: For data serialization
- Crow: Lightweight C++ web framework for REST API
- CMake: Build system
- AWS: Deployment environment

### System Architecture
![image](https://github.com/user-attachments/assets/078d952c-f828-4355-aab3-cb13251c88ef)

The architecture consists of the following components:

- REST API Gateway: Provides HTTP endpoints for client applications
- MOM Nodes: Leader and Follower nodes forming the cluster
- Queues: Store messages for point-to-point communication
- Topics: Enable publish-subscribe pattern messaging
- Clients: Producer and Consumer applications

## REST API Endpoints

### Queue Operations

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/queues` | GET | List all queues |
| `/queues/<name>?owner=<owner>` | POST | Create a new queue |
| `/queues/<name>?owner=<owner>` | DELETE | Delete a queue |
| `/queues/<name>/message?owner=<owner>&content=<content>` | POST | Send a message to a queue |
| `/queues/<name>/message?owner=<owner>` | GET | Receive a message from a queue |

### Topic Operations

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/topics` | GET | List all topics |
| `/topics/<name>?owner=<owner>` | POST | Create a new topic |
| `/topics/<name>?owner=<owner>` | DELETE | Delete a topic |
| `/topics/<name>/message?owner=<owner>&content=<content>` | POST | Publish a message to a topic |
| `/topics/<name>/message?owner=<owner>` | GET | Receive a message from a topic |

### Subscription Operations

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/subscribe_queue?topic_name=<topic_name>&topic_owner=<topic_owner>&queue_name=<queue_name>&queue_owner=<queue_owner>` | POST | Subscribe a queue to a topic |
| `/subscribe_queue?topic_name=<topic_name>&topic_owner=<topic_owner>&queue_name=<queue_name>&queue_owner=<queue_owner>` | DELETE | Unsubscribe a queue from a topic |
