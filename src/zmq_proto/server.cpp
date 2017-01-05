#include "zmq.hpp"
#include <string>
#include <iostream>
#include "message.pb.h"
#include <google/protobuf/text_format.h>

int main () {
    zmq::context_t context (1); //  Prepare our context and socket
//    zmq::socket_t socket(context, ZMQ_PAIR);
    zmq::socket_t socket(context, ZMQ_PULL);
    socket.bind ("tcp://*:5555");
//    socket.bind ("tcp://127.0.0.1:5555");

    while (true) {
        zmq::message_t request;
        socket.recv (&request); //  Wait for next request from client
        std::cout << "Received" << std::endl;
        tutorial::Person person;
        std::string msg_str(static_cast<char*>(request.data()), request.size());
        person.ParseFromString(msg_str);
        std::string text_str;
        google::protobuf::TextFormat::PrintToString(person, &text_str);
        std::cout << text_str << std::endl;
    }
    return 0;
}
