#pragma once
#include "Edge.hh"
#include <list>
#include <utility>
using std::list;

template <typename V, typename E>
class DGraph;

template <typename V, typename E>
class Vertex
{
    friend DGraph<V, E>;

  private:
    string key;
    V vexInfo;
    list<Edge<E>> eList;

  public:
    Vertex() = delete;
    Vertex(string key, V &&info) : key(std::move(key)), vexInfo(std::move(info)){};
    Vertex(string key, const V &info) : key(std::move(key)), vexInfo(info){};

  public:
    auto getEListBeg() -> typename list<Edge<E>>::iterator { return eList.begin(); };
    auto getEListEnd() -> typename list<Edge<E>>::iterator { return eList.end(); };
    auto getInfo() -> V & { return vexInfo; };
    auto getKey() { return key; };
    void setInfo(V &&info) { vexInfo = std::move(info); };
    void setInfo(const V &info) { vexInfo = info; };

  public:
    auto locateEdge(const string &to) -> typename list<Edge<E>>::iterator;
    void addEdge(Edge<E> &&newEdge);
    void addEdge(const Edge<E> &newEdge);
    void deleteEdge(const string &TVKey);
};
