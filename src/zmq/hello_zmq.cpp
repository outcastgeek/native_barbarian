
#include <zmq.hpp>
#include "zhelpers.hpp"

// Check this out: https://github.com/AnthonyCalandra/modern-cpp-features#template-argument-deduction-for-class-templates

template<typename... Args>
bool logicalAnd(Args... args) {
  // Binary folding.
  return (true && ... && args);
}

template<typename... Args>
auto sum(Args... args) {
  // Unary folding.
  return (... + args);
}

int main(int argc, char** argv){

  bool b = true;
  bool& b2 = b;

  auto boolRes = logicalAnd(b, b2, true); // == true
  std::cout << "Folded Boolean: " << boolRes << std::endl;

  auto sumRes = sum(1.0, 2.0f, 3); // == 6.0
  std::cout << "Folded Sum: " << sumRes << std::endl;

  zmq::context_t context(1);

  zmq::socket_t sink(context, ZMQ_ROUTER);
  sink.bind( "inproc://example");

  //  First allow 0MQ to set the identity
  zmq::socket_t anonymous(context, ZMQ_REQ);
  anonymous.connect( "inproc://example");

  s_send (anonymous, "ROUTER uses a generated 5 byte identity");
  s_dump (sink);

  //  Then set the identity ourselves
  zmq::socket_t identified (context, ZMQ_REQ);
  identified.setsockopt( ZMQ_IDENTITY, "PEER2", 5);
  identified.connect( "inproc://example");

  s_send (identified, "ROUTER socket uses REQ's socket identity");
  s_dump (sink);

  return 0;
}
