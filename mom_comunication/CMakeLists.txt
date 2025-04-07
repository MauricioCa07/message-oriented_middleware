cmake_minimum_required(VERSION 3.20)
project(momservice)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Explicitly find packages with basic REQUIRED
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)


add_library(protolib mom.proto)
target_link_libraries(protolib gRPC::grpc++)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate(TARGET protolib LANGUAGE cpp)
protobuf_generate(TARGET protolib LANGUAGE grpc
 GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
 PLUGIN "protoc-gen-grpc=${GRPC_CPP_PLUGIN}")

add_executable(server src/server.cc)
target_link_libraries(server protolib)