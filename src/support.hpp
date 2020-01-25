// Copyright (c) 2020 Andrew Sutton

#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include <cassert>

[[noreturn]] inline void unreachable()
{
  __builtin_unreachable();
}

#endif
