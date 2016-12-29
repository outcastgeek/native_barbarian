// $Id: //poco/1.4/Foundation/samples/Timer/src/Timer.cpp#1 $
// This sample demonstrates the Timer and Stopwatch classes.
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
// SPDX-License-Identifier:     BSL-1.0

#include "Poco/Timer.h"
#include "Poco/Thread.h"
#include "Poco/Stopwatch.h"
#include <iostream>

using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;

class TimerExample{
public:
        TimerExample(){ _sw.start();}

        void onTimer(Timer& timer){
                std::cout << "Callback called after " << _sw.elapsed()/1000 << " milliseconds." << std::endl;
        }
private:
        Stopwatch _sw;
};

// Check this out: https://github.com/AnthonyCalandra/modern-cpp-features#template-argument-deduction-for-class-templates

class context_t;

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

  TimerExample example;
  Timer timer(250, 500);
  timer.start(TimerCallback<TimerExample>(example, &TimerExample::onTimer));

  Thread::sleep(5000);
  timer.stop();
  return 0;
}
