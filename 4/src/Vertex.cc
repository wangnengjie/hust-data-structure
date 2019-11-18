#include "Vertex.hh"
#include <stdexcept>

template <typename V, typename E>
void Vertex<V, E>::addEdge(Edge<E> &&newEdge)
{
    eList.push_back(newEdge); // list<>::push_back has use std::move
}

template <typename V, typename E>
void Vertex<V, E>::addEdge(const Edge<E> &newEdge)
{
    eList.push_back(newEdge);
}

template <typename V, typename E>
void Vertex<V, E>::deleteEdge(const string &TVKey)
{
    typename list<Edge<E>>::iterator pos = std::find_if(
        eList.begin(), eList.end(), [&TVKey](const Edge<E> &e) { return TVKey == e.getTo(); });
    if (pos == eList.end())
    {
        throw std::logic_error("[Error]: Vertex<" + key + "> does not has a edge to Vertex<" +
                               TVKey + ">");
    }
    eList.erase(pos);
}

template <typename V, typename E>
auto Vertex<V, E>::locateEdge(const string &to) -> typename list<Edge<E>>::iterator
{
    return std::find_if(eList.begin(), eList.end(),
                        [&to](const Edge<E> &e) { return to == e.getTo(); });
}
