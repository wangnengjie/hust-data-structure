#include "DGraph.hh"
#include <unordered_set>

template <typename V, typename E>
DGraph<V, E>::DGraph(const list<Vertex<V, E>> &VList, const list<Edge<E>> &EList)
{
    // check if same key in list
    std::unordered_set<string> keySet;
    for (const Vertex<V, E> &vertex : VList)
    {
        if (keySet.find(vertex.getKey()) == keySet.end())
        {
            throw create_graph_error(
                "[Error]: Your input vertices have duplicate key: " + vertex.getKey() + " !");
        }
        keySet.insert(vertex.getKey());
    }

    vertexList = VList;
    vexNum = VList.size();

    for (const Edge<E> &edge : EList)
    {
        auto VPos = locateVex(edge.getFrom());
        if (VPos == VList.end())
        {
            throw create_graph_error("[Error]: Vertex<" + edge.getFrom() + "> does not exist");
        }
        auto EPos = VPos->locateEdge(edge.getTo());
        if (EPos != VPos->getEListEnd())
        {
            throw create_graph_error("[Error]: You should not input two same edge<" +
                                     edge.getFrom() + " -> " + edge.getTo() + ">");
        }
        VPos->addEdge(edge);
    }

    edgeNum = EList.size();
}

template <typename V, typename E>
auto DGraph<V, E>::locateVex(const string &key) -> typename list<Vertex<V, E>>::iterator
{
    return std::find_if(vertexList.begin(), vertexList.end(),
                        [&key](const Vertex<V, E> &v) { return v.getKey() == key; });
}

template <typename V, typename E>
void DGraph<V, E>::putVex(Vertex<V, E> &&vertex)
{
    auto pos = locateVex(vertex.getKey());
    if (pos != vertexList.end())
    {
        throw std::logic_error("[Error]: Vertex<" + vertex.getKey() + "> has existed!");
    }
    vertexList.push_back(vertex);
}

template <typename V, typename E>
void DGraph<V, E>::putVex(const Vertex<V, E> &vertex)
{
    auto pos = locateVex(vertex.getKey());
    if (pos != vertexList.end())
    {
        throw std::logic_error("[Error]: Vertex<" + vertex.getKey() + "> has existed!");
    }
    vertexList.push_back(vertex);
}

template <typename V, typename E>
auto DGraph<V, E>::firstAdjVex(const string &key) -> typename list<Vertex<V, E>>::iterator
{
    auto pos = locateVex(key);
    if (pos == vertexList.end())
    {
        throw std::logic_error("[Error]: Vertex<" + key + "> does not exist!");
    }
    if (pos->getEListBeg() == pos->getEListEnd())
    {
        return vertexList.end();
    }
    return locateVex(pos->getEListBeg()->getTo());
}
// Todo: here unfinish
template <typename V, typename E>
auto DGraph<V, E>::nextAdjVex(const string &key, const string &refKey) ->
    typename list<Vertex<V, E>>::iterator
{
    //    auto vpos = locateVex(key);
    //    if (vpos == vertexList.end())
    //    {
    //        throw std::logic_error("[Error]: Vertex<" + key + "> does not exist!");
    //    }
    //    auto epos = vpos->locateEdge(refKey);

    return list<Vertex<V, E>>::iterator();
}

template <typename V, typename E>
void DGraph<V, E>::insertVex(Vertex<V, E> &&newVex)
{
}

template <typename V, typename E>
void DGraph<V, E>::insertVex(const Vertex<V, E> &newVex)
{
}

template <typename V, typename E>
void DGraph<V, E>::deleteVex(const string &key)
{
}

template <typename V, typename E>
void DGraph<V, E>::insertEdge(Edge<E> &&edge)
{
}

template <typename V, typename E>
void DGraph<V, E>::insertEdge(const Edge<E> &edge)
{
}

template <typename V, typename E>
void DGraph<V, E>::deleteEdge(const string &fromKey, const string &toKey)
{
}

template <typename V, typename E>
void DGraph<V, E>::DFS(std::function<void(Vertex<V, E>)> f)
{
}
template <typename V, typename E>
void DGraph<V, E>::BFS(std::function<void(Vertex<V, E>)> f)
{
}
