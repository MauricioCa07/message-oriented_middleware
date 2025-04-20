cmake_minimum_required(VERSION 3.20)
project(momservice)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(absl REQUIRED CONFIG)
find_package(Threads REQUIRED)
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)

# Biblioteca para los archivos proto de la API REST
add_library(protolib STATIC
    ${CMAKE_CURRENT_BINARY_DIR}/../protos/api_rest/mom.pb.cc
    ${CMAKE_CURRENT_BINARY_DIR}/../protos/api_rest/mom.grpc.pb.cc
)

# Añadir biblioteca para los archivos proto de mom_to_mom
add_library(momtomomproto STATIC
    ${CMAKE_CURRENT_BINARY_DIR}/../protos/mom_to_mom/mom_to_mom.pb.cc
    ${CMAKE_CURRENT_BINARY_DIR}/../protos/mom_to_mom/mom_to_mom.grpc.pb.cc
)

target_include_directories(protolib PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
    ${grpc_INCLUDE_DIRS}
)

target_include_directories(momtomomproto PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
    ${grpc_INCLUDE_DIRS}
)

set(SERVER_SRCS
    src/server.cc
    src/queue/queue_obj.cc
    src/queue/queue_list.cc
    src/topic/topic_obj.cc
    src/topic/topic_list.cc
    src/node/node_impl.cc
    src/message/message.cc
    src/mom_to_mom/communication_mom_to_mom.cc
    src/mom_impl/mom_impl.cc
    src/mom_to_mom/communication_mom_stub.cc
)

add_executable(server ${SERVER_SRCS})

target_link_libraries(server
    PRIVATE
    protolib
    momtomomproto
    ${Protobuf_LIBRARIES}
    gRPC::grpc++
    gRPC::grpc
    absl::strings
    absl::synchronization
    utf8_validity
    Threads::Threads
    dl
)

target_include_directories(server PRIVATE
    ${Protobuf_INCLUDE_DIRS}
    ${grpc_INCLUDE_DIRS}
)