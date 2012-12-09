// Copyright 2012, Matthias Andreas Benkard.

#include "cells.hpp"

#include <memory>
#include <iostream>

struct unit { };

using namespace cells;
using std::cout;
using std::endl;

typedef formula_cell<double> fcell;
typedef shared_ptr<fcell>    sfcell;
typedef formula_cell<unit>   ucell;
typedef shared_ptr<ucell>    sucell;

int main(int argc, char** argv) {
  sfcell x0 = fcell::make();
  sfcell x1 = fcell::make();
  sfcell x2 = fcell::make();
  sfcell y = fcell::make();
  sfcell z = fcell::make();
  sucell a = ucell::make();
  sucell b = ucell::make();

  with_transaction([=](){
    x0->reset(10);
    x1->reset([=](){ return *x0 + 5; });
    x2->reset([=](){ return *x0 * 2; });
    y->reset([=](){ return *x1 * *x2; });
    z->reset([=](){ return *x0 * *y; });
    a->reset([=]() -> unit { cout << "z is now " << *z << "." << endl; return unit(); });
    b->reset([=]() -> unit { cout << "x2 is now " << *x2 << "." << endl; return unit(); });
  });

  x0->reset(15);
  x0->reset(-20);
  y->reset(-3);
  x1->reset([=]() { return (double)*x0; });
  y->reset([=]() { return *x1 + *x2; });
}


/*
 * z
 * |\
 * | \
 * |  \
 * |   \
 * |    \
 * |     \
 * |      \
 * |       y
 * |      /|
 * |     / |
 * |    /  |
 * |   x1  x2
 * |  /    |
 * | /     |
 * x0------+
 */
