#pragma once
#include "Edge.hh"
#include "Vertex.hh"
#include <functional>
#include <queue>
#include <stdexcept>
#include <unordered_set>

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
    /**
     * create a directed graph
     * @param VList the list of vertex
     * @param edgeList the list of edge
     */
    DGraph(const list<Vertex<V, E>> &VList, const list<Edge<E>> &edgeList);

  public:
    auto getVexNum() const { return vexNum; };
    auto getEdgeNum() const { return edgeNum; };
    auto getVListBeg() const -> typename list<Vertex<V, E>>::const_iterator
    {
        return vertexList.cbegin();
    };
    auto getVListEnd() const -> typename list<Vertex<V, E>>::const_iterator
    {
        return vertexList.cend();
    };
    /**
     * get the vertex
     * @param key the unique key of vertex
     * @return a const iterator point to the vertex which may point to end
     */
    auto locateVex(const string &key) const -> typename list<Vertex<V, E>>::const_iterator;

  private:
    /**
     * get the vertex
     * @param key the unique key of vertex
     * @return a iterator point to the vertex which may point to end
     */
    auto locateVertex(const string &key) -> typename list<Vertex<V, E>>::iterator;

  public:
    /**
     * update the value or info of vertex
     * @param key the unique key of vertex
     * @param value new value or info of the vertex
     */
    void putVex(const string &key, V &&value);
    /**
     * update the value or info of vertex
     * @param key the unique key of vertex
     * @param value new value or info of the vertex
     */
    void putVex(const string &key, const V &value);
    /**
     * insert a new vertex
     * @param newVex vertex
     */
    void insertVex(Vertex<V, E> &&newVex);
    /**
     * insert a new vertex
     * @param newVex vertex
     */
    void insertVex(const Vertex<V, E> &newVex);
    /**
     * delete vertex based on key
     * @param key the unique key of the vertex to delete
     */
    void deleteVex(const string &key);

  public:
    /**
     * insert a new edge
     * @param edge edge
     */
    void insertEdge(Edge<E> &&edge);
    /**
     * insert a new edge
     * @param edge edge
     */
    void insertEdge(const Edge<E> &edge);
    /**
     * delete edge by it's begin and end
     * @param fromKey the unique key of begin vertex
     * @param toKey the unique key of end vertex
     */
    void deleteEdge(const string &fromKey, const string &toKey);

  public:
    /**
     * find the adj vertex of a vertex
     * @param key the unique key of the vertex
     * @return a iterator point to the target vertex which may be point to end
     */
    auto firstAdjVex(const string &key) const -> typename list<Vertex<V, E>>::const_iterator;
    /**
     * find the next adj vertex of a vertex based on another adj vertex
     * @param key the unique key of base vertex
     * @param refKey the unique key of reference adj vertex
     * @return a iterator point to the target vertex which may point to end
     */
    auto nextAdjVex(const string &key, const string &refKey) const ->
        typename list<Vertex<V, E>>::const_iterator;

  public:
    /**
     * DFS
     * @param f visit func(const Vertex<V,E> &)
     */
    void DFSTraverse(std::function<void(const Vertex<V, E> &)> f) const;
    /**
     * BFS
     * @param f visit func(const Vertex<V,E> &)
     */
    void BFSTraverse(std::function<void(const Vertex<V, E> &)> f) const;

  private:
    /**
     * DFS helper
     * @param v current vertex
     * @param keySet a set which save the visited vertex
     * @param f visit func(const Vertex<V,E> &)
     */
    void dfs(const Vertex<V, E> &v, std::unordered_set<string> &keySet,
             std::function<void(const Vertex<V, E> &)> f) const;
};

template <typename V, typename E>
DGraph<V, E>::DGraph(const list<Vertex<V, E>> &VList, const list<Edge<E>> &EList)
{
    // check if same key in list
    std::unordered_set<string> keySet;
    for (const Vertex<V, E> &vertex : VList)
    {
        if (keySet.find(vertex.getKey()) != keySet.end())
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
        auto VPos = locateVertex(edge.getFrom());
        auto VPosTo = locateVertex(edge.getTo());
        if (VPos == getVListEnd())
        {
            throw create_graph_error("[Error]: Vertex<" + edge.getFrom() + "> does not exist");
        }
        if (VPosTo == getVListEnd())
        {
            throw create_graph_error("[Error]: Vertex<" + edge.getTo() + "> does not exist");
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
auto DGraph<V, E>::locateVertex(const string &key) -> typename list<Vertex<V, E>>::iterator
{
    return std::find_if(vertexList.begin(), vertexList.end(),
                        [&key](const Vertex<V, E> &v) { return v.getKey() == key; });
}

template <typename V, typename E>
auto DGraph<V, E>::locateVex(const string &key) const -> typename list<Vertex<V, E>>::const_iterator
{
    return std::find_if(vertexList.begin(), vertexList.end(),
                        [&key](const Vertex<V, E> &v) { return v.getKey() == key; });
}

template <typename V, typename E>
void DGraph<V, E>::putVex(const string &key, V &&value)
{
    auto pos = locateVertex(key);
    if (pos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + key + "> does not exist!");
    }
    pos->setInfo(value);
}

template <typename V, typename E>
void DGraph<V, E>::putVex(const string &key, const V &value)
{
    auto pos = locateVertex(key);
    if (pos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + key + "> does not exist!");
    }
    pos->setInfo(value);
}

template <typename V, typename E>
auto DGraph<V, E>::firstAdjVex(const string &key) const ->
    typename list<Vertex<V, E>>::const_iterator
{
    auto pos = locateVex(key);
    if (pos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + key + "> does not exist!");
    }
    if (pos->getEListBeg() == pos->getEListEnd())
    {
        return getVListEnd();
    }
    return locateVex(pos->getEListBeg()->getTo());
}

template <typename V, typename E>
auto DGraph<V, E>::nextAdjVex(const string &key, const string &refKey) const ->
    typename list<Vertex<V, E>>::const_iterator
{
    auto vpos = locateVex(key);
    if (vpos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + key + "> does not exist!");
    }
    auto epos = vpos->locateEdge(refKey);
    if (epos != vpos->getEListEnd() && ++epos != vpos->getEListEnd())
    {
        return locateVex(epos->getTo());
    }
    return getVListEnd();
}

template <typename V, typename E>
void DGraph<V, E>::insertVex(Vertex<V, E> &&newVex)
{
    auto pos = locateVertex(newVex.getKey());
    if (pos != getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + newVex.getKey() + "> has existed!");
    }
    vertexList.push_back(newVex);
    vexNum++;
}

template <typename V, typename E>
void DGraph<V, E>::insertVex(const Vertex<V, E> &newVex)
{
    auto pos = locateVertex(newVex.getKey());
    if (pos != getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + newVex.getKey() + "> has existed!");
    }
    vertexList.push_back(newVex);
    vexNum++;
}

template <typename V, typename E>
void DGraph<V, E>::deleteVex(const string &key)
{
    auto pos = locateVertex(key);
    if (pos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + key + "> does not exist!");
    }
    std::for_each(vertexList.begin(), vertexList.end(),
                  [&key](Vertex<V, E> &v) { v.deleteEdge(key); });
    vertexList.erase(pos);
    vexNum--;
}

template <typename V, typename E>
void DGraph<V, E>::insertEdge(Edge<E> &&edge)
{
    auto v1pos = locateVertex(edge.getFrom());
    auto v2pos = locateVertex(edge.getTo());
    if (v1pos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + edge.getFrom() + "> does not exist!");
    }
    if (v2pos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + edge.getTo() + "> does not exist!");
    }
    v1pos->addEdge(edge);
    edgeNum++;
}

template <typename V, typename E>
void DGraph<V, E>::insertEdge(const Edge<E> &edge)
{
    auto v1pos = locateVertex(edge.getFrom());
    auto v2pos = locateVertex(edge.getTo());
    if (v1pos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + edge.getFrom() + "> does not exist!");
    }
    if (v2pos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + edge.getTo() + "> does not exist!");
    }
    v1pos->addEdge(edge);
    edgeNum++;
}

template <typename V, typename E>
void DGraph<V, E>::deleteEdge(const string &fromKey, const string &toKey)
{
    auto vpos = locateVertex(fromKey);
    if (vpos == getVListEnd())
    {
        throw std::logic_error("[Error]: Vertex<" + fromKey + "> does not exist!");
    }
    vpos->deleteEdge(toKey);
    edgeNum--;
}

template <typename V, typename E>
void DGraph<V, E>::DFSTraverse(std::function<void(const Vertex<V, E> &)> f) const
{
    std::unordered_set<string> keySet;
    for (const Vertex<V, E> &v : vertexList)
    {
        if (keySet.size() == vertexList.size())
        {
            break;
        }
        if (keySet.find(v.getKey()) == keySet.end())
        {
            dfs(v, keySet, f);
        }
    }
}

template <typename V, typename E>
void DGraph<V, E>::dfs(const Vertex<V, E> &v, std::unordered_set<string> &keySet,
                       std::function<void(const Vertex<V, E> &)> f) const
{
    keySet.insert(v.getKey());
    f(v);
    for (auto epos = v.getEListBeg(); epos != v.getEListEnd(); epos++)
    {
        if (keySet.size() == vertexList.size())
        {
            break;
        }
        if (keySet.find(epos->getTo()) == keySet.end())
        {
            dfs(*locateVex(epos->getTo()), keySet, f);
        }
    }
}

template <typename V, typename E>
void DGraph<V, E>::BFSTraverse(std::function<void(const Vertex<V, E> &)> f) const
{
    std::queue<typename list<Vertex<V, E>>::const_iterator> vexQue;
    std::unordered_set<string> keySet;
    for (auto v = getVListBeg(); v != getVListEnd(); v++)
    {
        if (keySet.find(v->getKey()) == keySet.end())
        {
            vexQue.push(v);
            while (!vexQue.empty())
            {
                auto vex = vexQue.front();
                vexQue.pop();
                f(*vex);
                keySet.insert(vex->getKey());
                for (auto epos = vex->getEListBeg(); epos != vex->getEListEnd(); epos++)
                {
                    if (keySet.find(epos->getTo()) == keySet.end())
                    {
                        vexQue.push(locateVex(epos->getTo()));
                        keySet.insert(epos->getTo());
                    }
                }
            }
        }
    }
}
