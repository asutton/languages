// Copyright (c) 2020 Andrew Sutton

#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include "support.hpp"

#include <cstddef>

#include <array>
#include <concepts>
#include <span>

// Structural components

template<typename T>
struct nullary
{
  static constexpr std::size_t arity_value = 0;

  std::size_t arity() const
  {
    return 0;
  }

  std::span<T const* const, 0> children() const
  {
    return {};
  }

  std::span<T*, 0> children()
  {
    return {};
  }
};

template<typename T, std::size_t N>
struct array
{
  static constexpr std::size_t arity_value = N;

  array(std::initializer_list<T*> list)
  {
    assert(list.size() == N);
    std::copy(list.begin(), list.end(), m_kids.begin());
  }

  constexpr std::size_t arity() const
  {
    return N;
  }

  std::span<T const* const, N> children() const
  {
    return {m_kids.data(), N};
  }

  std::span<T*, N> children()
  {
    return {m_kids.data(), N};
  }

  T const* child(std::size_t n) const
  {
    assert(n < N);
    return m_kids[n];
  }

  T* child(std::size_t n)
  {
    assert(n < N);
    return m_kids[n];
  }

  std::array<T*, N> m_kids;
};

template<typename T>
struct unary : array<T, 1>
{
  unary(T* t1)
    : array<T, 1>({t1})
  { }

  using array<T, 1>::child;

  T const* child() const
  {
    return this->child(0);
  }

  T* child()
  {
    return this->child(0);
  }
};

template<typename T>
struct binary : array<T, 2>
{
  binary(T* t1, T* t2)
    : array<T, 2>({t1, t2})
  { }
};

template<typename T>
struct ternary : array<T, 3>
{
  ternary(T* t1, T* t2, T* t3)
    : array<T, 3>({t1, t2, t3})
  { }
};


// Kinding

/// A class used to associate a kind with a node.
template<auto K>
struct kind_of
{
  static constexpr decltype(K) this_kind = K;
};


// Concepts

/// True for all tree nodes that have a fixed number of nodes.
template<typename T>
concept array_tree =
  requires(T* p)
  {
    T::arity_value;
  };

/// True for all array trees with arity N.
template<typename T, std::size_t N>
concept array_k_tree = array_tree<T> && (T::arity_value == N);

/// True for all array trees with arity 0.
template<typename T>
concept leaf_tree = array_k_tree<T, 0>;


// Testing and casting

template<typename T, typename U>
bool is(U const* u)
{
  return u->kind() == T::this_kind;
}

template<typename T, typename U>
T const* cast(U const* u)
{
  assert(is<T>(u));
  return static_cast<T const*>(u);
}

template<typename T, typename U>
T* cast(U* u)
{
  assert(is<T>(u));
  return static_cast<T*>(u);
}

template<typename T, typename U>
T const* maybe_cast(U const* u)
{
  if (is<T>(u))
    return static_cast<T const*>(u);
  return nullptr;
}

template<typename T, typename U>
T* maybe_cast(U* u)
{
  if (is<T>(u))
    return static_cast<T*>(u);
  return nullptr;
}

#endif
