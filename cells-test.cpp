// Copyright 2012, Matthias Andreas Benkard.
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see
// <http://www.gnu.org/licenses/>.

#include "cells.hpp"

#include <cstdlib>
#include <memory>
#include <iostream>

struct unit { };

using namespace cells;
using std::cout;
using std::endl;

typedef formula_cell<double> fcell;
typedef formula_cell<unit>   ucell;


int main(int argc, char** argv) {
  fcell x0, x1, x2, y;
  ucell b;

  {
    fcell z;
    ucell a;
    with_transaction([&](){
      x0.reset(10);
      x1.reset([&](){ return *x0 + 5; });
      x2.reset([&](){ return *x0 * 2; });
      y.reset([&](){ return *x1 * *x2; });
      z.reset([&](){ return *x0 * *y; });
      a.reset([&]() -> unit { cout << "z is now " << *z << "." << endl; return unit(); });
      b.reset([&]() -> unit { cout << "x2 is now " << *x2 << "." << endl; return unit(); });
    });
  
    x0.reset(15);
    x0.reset(-20);
    y.reset(-3);
    x1.reset([&]() { return (double)*x0; });
    y.reset([&]() { return *x1 + *x2; });
  }

  x0.reset(10);  //z and a are not active anymore, so only b will
                 //produce output.
  
  return EXIT_SUCCESS;
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
