#include <list>
#include <string>

using std::list;
using std::string;

// 弧节点
template <typename E> class Arc
{
  private:
    string _key; // 弧指向的顶点的key
    E _info;     // 弧上信息类

  public:
    Arc() = delete;
    Arc(string key, E elem) : _key(key), _info(elem){};
    const E &getInfo() { return _info; };
    void setInfo(E nInfo) { _info = nInfo; };
};

// 顶点
template <typename V, typename E> class Vertex
{
  private:
    string _key;
    V _info;
    list<Arc<E>> _arcList;

  public:
    Vertex() = delete;
    Vertex(string key, V elem, list<Arc<E>> firstArc = list<Arc<E>>())
        : _key(key), _info(elem), _arcList(firstArc){};
    const V &getInfo() { return _info; };
    void setInfo(V nInfo) { _info = nInfo; };
};

// 有向图
template <typename V, typename E> class Graph
{
  private:
    int _vexnum, _arcnum;
    list<Vertex<V, E>> _vertexList;

  public:
    Graph() : _vexnum(0), _arcnum(0){};
    Graph(list<Vertex<V, E>> vertexList, list<Arc<E>> arcList)
        : _vertexList(vertexList){};
};