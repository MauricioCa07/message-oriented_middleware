cmake_minimum_required(VERSION 3.10)


project(rest_api)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(absl REQUIRED CONFIG)
find_package(Crow REQUIRED)



find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)


add_library(protolib STATIC 
    ${CMAKE_CURRENT_BINARY_DIR}/../protos/rest_api/mom.pb.cc
    ${CMAKE_CURRENT_BINARY_DIR}/../protos/rest_api/mom.grpc.pb.cc
)

target_include_directories(protolib PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${Protobuf_INCLUDE_DIRS}
    ${grpc_INCLUDE_DIRS} 
)


set(SERVER_SRCS
    src/rest_api.cc
    src/rest_impl/rest_impl.cc
    src/node/node_impl.cc
)

add_executable(rest_api ${SERVER_SRCS})


target_link_libraries(rest_api
    PRIVATE 
    protolib 
    ${Protobuf_LIBRARIES} 
    gRPC::grpc++       
    gRPC::grpc          
    absl::strings         
    absl::synchronization 
    utf8_validity
    Threads::Threads     
    dl                 
)

target_include_directories(rest_api PRIVATE
    ${Protobuf_INCLUDE_DIRS}
    ${grpc_INCLUDE_DIRS}
)

