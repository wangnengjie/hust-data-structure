#pragma once
#include "Edge.hh"
#include "Vertex.hh"
#include <functional>
#include <stdexcept>

class create_graph_error : public std::logic_error
{
  public:
    explicit create_graph_error(const string &s) : std::logic_error(s){};
};

template <typename V, typename E>
class DGraph
{
  private:
    unsigned int vexNum{0};
    unsigned int edgeNum{0};
    list<Vertex<V, E>> vertexList;

  public:
    DGraph(const list<Vertex<V, E>> &vertexList, const list<Edge<E>> &edgeList);

  public:
    auto getVexNum() { return vexNum; };
    auto getEdgeNum() { return edgeNum; };

  public:
    auto locateVex(const string &key) -> typename list<Vertex<V, E>>::iterator;
    void putVex(Vertex<V, E> &&vertex);
    void putVex(const Vertex<V, E> &vertex);
    auto firstAdjVex(const string &key) -> typename list<Vertex<V, E>>::iterator;
    auto nextAdjVex(const string &key, const string &refKey) ->
        typename list<Vertex<V, E>>::iterator;
    void insertVex(Vertex<V, E> &&newVex);
    void insertVex(const Vertex<V, E> &newVex);
    void deleteVex(const string &key);
    void insertEdge(Edge<E> &&edge);
    void insertEdge(const Edge<E> &edge);
    void deleteEdge(const string &fromKey, const string &toKey);
    void DFS(std::function<void(Vertex<V, E>)> f);
    void BFS(std::function<void(Vertex<V, E>)> f);
};
