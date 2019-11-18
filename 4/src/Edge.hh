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
    auto setFrom(const string &newFrom) -> Edge<E> &;
    auto setTo(const string &newTo) -> Edge<E> &;

  public:
    Edge() = delete;
    Edge(string from, string to, E &&info)
        : from(std::move(from)), to(std::move(to)), edgeInfo(std::move(info)){};
    Edge(string from, string to, const E &info)
        : from(std::move(from)), to(std::move(to)), edgeInfo(info){};
    auto getFrom() { return from; };
    auto getTo() { return to; };
    auto getInfo() -> E & { return edgeInfo; };
    auto setInfo(E &&info) -> Edge<E> &;
    auto setInfo(const E &info) -> Edge<E> &;
};
