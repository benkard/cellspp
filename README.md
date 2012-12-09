# A Simple Dataflow Library for C++

## Introduction

You may have heard of lazy evaluation.  It works like this: You
specify the meaning of an expression not by putting a value into a
box, but by declaratively writing down a way of computing the
expression.  Whenever someone asks for the value of an expression, it
is computed on-demand and cached.  Thus, we have a dependency graph
between expressions (that is hopefully acyclic).  Since we compute
only what someone actually asks for, control flows from the consumer
to the producer, up the dependency chain.  The data is passive,
waiting for the consumer to ask for things to be computed; the
consumer actively initiates all computation.  This is the
**pull-model** of declarative computation.

Rather less widespread, there is a technique that is dual to lazy
evaluation.  As in lazy evaluation, you specify the meaning of
something by writing down how to compute it from other things.  But
now, you do not wait for someone to ask for the value.  Instead, you
compute the value right away; and whenever one of the inputs changes,
you immediately recompute the value.  Thus, control flows from the
producer to the consumer, down the dependency chain.  The data is
active, reacting to events from the outside world as soon as they
happen; the consumer sits waiting passively and gets notified whenever
something changes.  This is the **push-model** of declarative
computation.  It is sometimes called the *spreadsheet model*, since it
operates like a spreadsheet: You have a bunch of cells, and whenever
you modify a cell, the change immediately propagates to all dependent
cells, prompting visual adjustments as well.

But reactive patterns naturally arise not just in spreadsheets, but
also in multimedia programming.  Take a game object, a person, say,
consisting of various parts, such as legs, arms, and a head.  You may
want to draw each part independently from the others, but you always
know the relative locations of the parts with regard to the object.
Whenever you move the object, you want the parts to move accordingly.
Hence, while specifying something like `arm.x := person.x - 10` is
very natural, you expect `arm.x` to update itself whenever `person.x`
changes.  In fact, the multimedia-oriented scripting language JavaFX
provides just such a kind of limited dataflow mechanism.


## Usage

This is a header-only library.  Simply put all the `.hpp` files
wherever your compiler can find them and `#include <cells.hpp>`.

The API primarily consists of the `cell<T>` and `formula_cell<T>`
class templates.  Using a `formula_cell<T>` is easy: simply construct
one and use the `reset` method to set a formula to compute the value
of the cell:

    typedef formula_cell<double> fcell;
    
    fcell x;
    x.reset([](){ return 5; });
    
For convenience, you can also just write something like `x->reset(5);`
for setting a constant value.

In order to create a dependent cell, simply make use of the other
cell's value in the formula:

    fcell double_x;
    double_x.reset([&](){ return 2 * x.get(); });

From now on, whenever `x` changes, `double_x` will be updated
accordingly.

You can create change event observers by writing formulas that make
use of an observed cell and return a dummy value:

    fcell simple_observer;
    simple_observer.reset([&]() -> double {
      (void)double_x.get();
      std::cout << "double_x has changed!" << std::endl;
      return 0;
    });


## Acknowledgments

This work was inspired by Kenny Tilton's Cells library, which extends
the Common Lisp Object System with dataflow features.


## License

Copyright 2012, Matthias Andreas Benkard.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this program.  If not, see
http://www.gnu.org/licenses/.
