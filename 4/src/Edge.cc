#include "Edge.hh"

template <typename E>
auto Edge<E>::setInfo(E &&info) -> Edge<E> &
{
    edgeInfo = std::move(info);
    return *this;
}

template <typename E>
auto Edge<E>::setInfo(const E &info) -> Edge<E> &
{
    edgeInfo = info;
    return *this;
}

template <typename E>
auto Edge<E>::setFrom(const string &newFrom) -> Edge<E> &
{
    from = newFrom;
    return *this;
}

template <typename E>
auto Edge<E>::setTo(const string &newTo) -> Edge<E> &
{
    to = newTo;
    return *this;
}
