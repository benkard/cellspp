#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <functional>
#include <memory>
#include <future>

#include "dynvars.hpp"

#include <boost/signals2.hpp>

using namespace ::std;
using namespace ::boost::signals2;
using namespace ::dynvars;

#define thread_local __thread
thread_local dynvar<string> greetee;

function<void ()>
make_greeter(const string& greeting) {
  return [=]() {
    cout << greeting << " " << *greetee << "!" << endl;
  };
};

int
main(int argc, char **argv) {
  greetee = "nobody";
  signal<void ()> sig;

  sig.connect(make_greeter("Hi"));

  sig();
  with<string, void>(greetee, "luser", [&](){ sig(); });
  with<string, void>(greetee, "geek",  [&](){ sig(); });
  sig();

  return EXIT_SUCCESS;
}
