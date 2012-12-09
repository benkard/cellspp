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

#ifndef DYNVARS_HPP
#define DYNVARS_HPP

#include <functional>
#include <list>

#define thread_local __thread

namespace dynvars {

template <typename T>
class dynvar {
private:
  std::list<T> value_stack;
public:
  dynvar() { };
  dynvar(T val);
  dynvar<T>& operator =(T val);
  void push(T val);
  void pop();
  T& operator *();
  T* operator ->();
  operator bool() const;
};

template <typename R>
class dyn {
  dynvar<R>& myvar;
public:
  dyn(dynvar<R>& var, R val);
  ~dyn();
};

template <typename R, typename T>
T
with(dynvar<R>& var, R val, std::function<T ()> f);

}

#endif  //DYNVARS_HPP

#include "dynvars-impl.hpp"
