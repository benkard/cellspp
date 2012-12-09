// Copyright 2012, Matthias Andreas Benkard.

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
