// Copyright 2012, Matthias Andreas Benkard.
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program.  If not, see
// <http://www.gnu.org/licenses/>.

#pragma once

#ifndef CELLS_HPP
#define CELLS_HPP

#include <functional>
#include <memory>
#include <forward_list>
#include <algorithm>

namespace cells {

  class observer : public virtual std::enable_shared_from_this<observer> {
  private:
    std::forward_list<std::weak_ptr<observer>> dependents;
    std::forward_list<std::shared_ptr<observer>> dependencies;

    void clear_dependencies();
    void mark_dependents();

  protected:
    void mark();

  public:
    void add_dependent(std::shared_ptr<observer> dependent);
    void remove_dependent(observer* dependent);
    void reset_dependencies(std::forward_list<std::shared_ptr<observer>> const& newdeps);

    virtual void update() = 0;

    virtual ~observer();
  };


  template <typename T>
  class cell : public observer {
  private:
    T current_value;

  protected:
    cell();
    virtual void update();
    virtual T recompute(T) = 0;
    virtual T init() = 0;

  public:
    T& get();
    T& operator *() { return get(); }
    //T operator ()() { return get(); }
    operator T() { return get(); }

    virtual ~cell();
  };


  template <typename T>
  class formula_cell : public cell<T> {
    //friend class std::shared_ptr<formula_cell<T>>;
    //friend std::shared_ptr<formula_cell<T>> std::make_shared<formula_cell<T>>();
  private:
    std::function<T ()> formula;
    std::function<T (T old)> alt_formula;

  protected:
    formula_cell() { }
    virtual T recompute(T);
    virtual T init();

  public:
    //static std::shared_ptr<formula_cell<T>> make() { return std::make_shared<formula_cell<T>>(); }
    static std::shared_ptr<formula_cell<T>> make() { return std::shared_ptr<formula_cell<T>>(new formula_cell()); }

    void reset(T value);
    void reset(std::function<T ()>);
    void reset(std::function<T ()>, std::function<T (T old)>);

    virtual ~formula_cell();
  };

  static void with_transaction(std::function<void ()>);
}

#endif //CELLS_HPP

#include "cells-impl.hpp"
