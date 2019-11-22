#include "DGraph.hh"
#include <iostream>

void print(const Vertex<string, string> &v)
{
    std::cout << v.getKey() + "\t" + v.getInfo() << std::endl;
}

auto main() -> int
{
    try
    {
        std::list<Vertex<string, string>> vList;
        vList.emplace_back("asdasd", "aaaa");
        vList.emplace_back("dfis", "aaaa");
        vList.emplace_back("hzytql", "aaaa");
        vList.emplace_back("hqntql", "aaaa");
        list<Edge<string>> aList;
        aList.emplace_back("asdasd", "dfis", "aaaa");
        aList.emplace_back("asdasd", "hzytql", "aaaa");
        aList.emplace_back("dfis", "hqntql", "aaaa");
        DGraph<string, string> myGraph(vList, aList);
        auto p = myGraph.nextAdjVex("asdasd", "dfis");
        if (p != myGraph.getVListEnd())
        {
            std::cout << p->getKey() << std::endl;
        }
        myGraph.DFSTraverse(print);
    }
    catch (create_graph_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (std::logic_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (std::bad_alloc &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
