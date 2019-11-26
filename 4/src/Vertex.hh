#pragma once
#include "Edge.hh"
#include <list>
#include <stdexcept>
#include <utility>
using std::list;

template <typename V, typename E>
class Vertex
{
  private:
    string key;
    V vexInfo;
    list<Edge<E>> eList;

  public:
    Vertex() = delete;
    Vertex(string key, V &&info) : key(std::move(key)), vexInfo(std::move(info)){};
    Vertex(string key, const V &info) : key(std::move(key)), vexInfo(info){};

  public:
    auto locateEdge(const string &to) const -> typename list<Edge<E>>::const_iterator;
    auto getEListBeg() const -> typename list<Edge<E>>::const_iterator { return eList.cbegin(); };
    auto getEListEnd() const -> typename list<Edge<E>>::const_iterator { return eList.cend(); };
    auto getInfo() const -> const V & { return vexInfo; };
    auto getKey() const { return key; };
    void setInfo(V &&info) const { vexInfo = std::move(info); };
    void setInfo(const V &info) const { vexInfo = info; };

  public:
    void addEdge(Edge<E> &&newEdge);
    void addEdge(const Edge<E> &newEdge);
    void deleteEdge(const string &TVKey);

  public:
    friend std::ostream &operator<<(std::ostream &out, const Vertex<V, E> &v)
    {
        out << string("<key(") << v.getKey() << "),info(" << v.getInfo() << ")>";
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Vertex<V, E> &v)
    {
        in >> v.key >> v.vexInfo;
        return in;
    }
};

template <typename V, typename E>
void Vertex<V, E>::addEdge(Edge<E> &&newEdge)
{
    eList.push_back(std::move(newEdge));
}

template <typename V, typename E>
void Vertex<V, E>::addEdge(const Edge<E> &newEdge)
{
    eList.push_back(newEdge);
}

template <typename V, typename E>
void Vertex<V, E>::deleteEdge(const string &TVKey)
{
    typename list<Edge<E>>::iterator pos = locateEdge(TVKey);
    if (pos == eList.end())
    {
        throw std::logic_error("[Error]: Vertex<" + key + "> does not has a edge to Vertex<" +
                               TVKey + ">");
    }
    eList.erase(pos);
}

template <typename V, typename E>
auto Vertex<V, E>::locateEdge(const string &to) const -> typename list<Edge<E>>::const_iterator
{
    return std::find_if(eList.begin(), eList.end(),
                        [&to](const Edge<E> &e) { return to == e.getTo(); });
}
