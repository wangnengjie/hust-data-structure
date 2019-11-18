#include "Graph.hh"
#include <iostream>
auto main() -> int
{
    try
    {
        std::list<Vertex<string, string>> vList;
        vList.emplace_back("asdasd", "aaaa");
        vList.emplace_back("dfis", "aaaa");
        vList.emplace_back("hzytql", "aaaa");
        list<IArc<string>> aList;
        aList.emplace_back("asdasd", "dfis", "aaaa");
        aList.emplace_back("asdasd", "hzytql", "aaaa");
        Graph<string, string> myGraph(vList, aList);
        auto p = myGraph.nextAdjVex("asdasd", "dfis");
        if (p == nullptr)
        {
            std::cout << (p == nullptr) << std::endl;
        }
        else
        {
            std::cout << p->getKey() << std::endl;
        }
    }
    catch (create_graph_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (std::logic_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
