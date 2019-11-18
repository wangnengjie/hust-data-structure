#pragma once
#include <algorithm>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>

using std::list;
using std::string;

template <typename E>
class IArc
{
  public:
    string Fkey;
    string Tkey;
    E info;

    IArc(string from, string to, E &&elem)
        : Fkey(std::move(from)), Tkey(std::move(to)), info(elem){};
};

template <typename E>
class Arc
{
  private:
    string _key;
    E _info;

  public:
    Arc() = delete;

    Arc(string key, E &&elem) : _key(std::move(key)), _info(elem){};

    auto getKey() -> const string & { return _key; };

    auto getInfo() -> const E & { return _info; };

    void setInfo(E &&nInfo) { _info = nInfo; };
};

template <typename V, typename E>
class Vertex
{
  private:
    string _key;
    V _info;
    list<Arc<E>> _arcList;

  public:
    Vertex() = delete;

    Vertex(string key, V &&elem) : _key(std::move(key)), _info(elem){};

    auto getInfo() -> const V & { return _info; };

    auto getAList() -> list<Arc<E>> & { return _arcList; };

    auto getKey() -> const string & { return _key; };

    void setInfo(V &&nInfo) { _info = nInfo; };

    void addArc(Arc<E> &&newArc);

    void deleteArc(const string &target);
};

template <typename V, typename E>
class Graph
{

  private:
    int _vexnum{0};
    int _arcnum{0};
    list<Vertex<V, E>> _vertexList;

  public:
    Graph(list<Vertex<V, E>> &vertexList, list<IArc<E>> &arcList);

    Vertex<V, E> *locateVex(const string &key);

    void putVex(const string &key, V &&elem);

    auto firstAdjVex(const string &key) -> Vertex<V, E> *;

    auto nextAdjVex(const string &v, const string &w) -> Vertex<V, E> *;
};

class create_graph_error : public std::logic_error
{
  public:
    explicit create_graph_error(const string &s) : std::logic_error(s){};
};

template <typename V, typename E>
void Vertex<V, E>::addArc(Arc<E> &&newArc)
{
    auto pos =
        std::find_if(_arcList.begin(), _arcList.end(), [&newArc](Arc<E> &arc) {
            return newArc.getKey() == arc.getKey();
        });
    if (_arcList.end() != pos)
    {
        throw std::logic_error("[Error]: Arc has existed!");
    }
    _arcList.push_back(newArc);
}

template <typename V, typename E>
void Vertex<V, E>::deleteArc(const string &target)
{
    auto pos =
        std::find_if(_arcList.begin(), _arcList.end(),
                     [&target](Arc<E> &arc) { return target == arc.getKey(); });
    if (_arcList.end() == pos)
    {
        throw std::logic_error("[Error]: Arc does not exist!");
    }
    _arcList.erase(pos);
}

template <typename V, typename E>
Graph<V, E>::Graph(list<Vertex<V, E>> &vertexList, list<IArc<E>> &arcList)
{
    std::unordered_set<string> keySet;
    for (Vertex<V, E> &v : vertexList)
    {
        if (keySet.find(v.getKey()) == keySet.end())
        {
            keySet.insert(v.getKey());
        }
        else
        {
            throw create_graph_error(
                "[Error]: Your input vertices have duplicate key: " +
                v.getKey() + " !");
        }
    }
    _vertexList = vertexList;
    _vexnum = static_cast<int>(vertexList.size());
    for (auto &arc : arcList)
    {
        auto pos = locateVex(arc.Fkey);
        if (pos == nullptr)
        {
            throw create_graph_error("[Error]: Vertex key " + arc.Fkey +
                                     " does not exist!");
        }
        try
        {
            pos->addArc(Arc<E>(arc.Tkey, std::move(arc.info)));
        }
        catch (const std::logic_error &e)
        {
            throw create_graph_error(e.what());
        }
    }
    _arcnum = static_cast<int>(arcList.size());
}

template <typename V, typename E>
auto Graph<V, E>::locateVex(const string &key) -> Vertex<V, E> *
{
    for (auto be = _vertexList.begin(); be != _vertexList.end(); be++)
    {
        if (be->getKey() == key)
        {
            return &(*be);
        }
    }
    return nullptr;
}

template <typename V, typename E>
void Graph<V, E>::putVex(const string &key, V &&elem)
{
    Vertex<V, E> *pos = locateVex(key);
    if (pos == nullptr)
    {
        throw std::logic_error("[Error]: Vertex " + key + " does not exist!");
    }
    pos->setInfo(std::move(elem));
}

template <typename V, typename E>
auto Graph<V, E>::firstAdjVex(const string &key) -> Vertex<V, E> *
{
    Vertex<V, E> *pos = locateVex(key);
    if (pos == nullptr)
    {
        throw std::logic_error("[Error]: Vertex " + key + " does not exist!");
    }
    if (pos->getAList().empty())
    {
        throw std::logic_error("[Error]: Vertex " + key +
                               " does not have adjVex");
    }
    auto &firstArc = pos->getAList().front();
    return locateVex(firstArc.getKey());
}

template <typename V, typename E>
auto Graph<V, E>::nextAdjVex(const string &v, const string &w) -> Vertex<V, E> *
{
    Vertex<V, E> *pos = locateVex(v);
    if (pos == nullptr)
    {
        throw std::logic_error("[Error]: Vertex " + v + " does not exist!");
    }
    auto &AList = pos->getAList();
    typename list<Arc<E>>::iterator PToW =
        std::find_if(AList.begin(), AList.end(),
                     [&w](Arc<E> &arc) { return arc.getKey() == w; });
    if (PToW == AList.end())
    {
        throw std::logic_error("[Error]: Vertex " + w + " does not exist!");
    }
    if (++PToW == AList.end())
    {
        return nullptr;
    }
    return locateVex(PToW->getKey());
}
