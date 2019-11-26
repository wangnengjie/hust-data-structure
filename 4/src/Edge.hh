#pragma once
#include <string>
#include <utility>
using std::string;

template <typename E>
class Edge
{

  private:
    string from;
    string to;
    E edgeInfo;

  public:
    Edge() = delete;
    Edge(string from, string to, E &&info)
        : from(std::move(from)), to(std::move(to)), edgeInfo(std::move(info)){};
    Edge(string from, string to, const E &info)
        : from(std::move(from)), to(std::move(to)), edgeInfo(info){};
    auto getFrom() const { return from; };
    auto getTo() const { return to; };
    auto getInfo() const -> E & { return edgeInfo; };
    auto setInfo(E &&info) const -> Edge<E> &;
    auto setInfo(const E &info) const -> Edge<E> &;
};

template <typename E>
auto Edge<E>::setInfo(E &&info) const -> Edge<E> &
{
    edgeInfo = std::move(info);
    return *this;
}

template <typename E>
auto Edge<E>::setInfo(const E &info) const -> Edge<E> &
{
    edgeInfo = info;
    return *this;
}
