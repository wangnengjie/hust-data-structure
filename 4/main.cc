#include "DGraph.hh"
#include <fstream>
#include <iostream>
#include <memory>

using std::make_shared;
using std::shared_ptr;
/**
 * whether the graph is nullptr
 * @tparam V info type of vertex
 * @tparam E info type of edge
 * @param p a pointer -> graph
 */
template <typename V, typename E>
inline void shouldInit(const shared_ptr<DGraph<V, E>> &p)
{
    if (p == nullptr)
    {
        throw std::logic_error("[Error]: Graph has not initialized");
    }
};
/**
 * print vertex to shell
 * @tparam V info type of vertex
 * @tparam E info type of edge
 * @param v vertex
 */
template <typename V, typename E>
void printVex(const Vertex<V, E> &v);
/**
 * print the option menu
 */
void printMenu();
/**
 * read and create vertex list from stream
 * @param in istream
 * @param size the amount of vertex
 * @return vertex list
 */
auto readVex(std::istream &in, unsigned int size) -> list<Vertex<int, int>>;
/**
 * read and create edge list from stream
 * @param in istream
 * @param size the amount of edge
 * @return edge list
 */
auto readEdge(std::istream &in, unsigned int size) -> list<Edge<int>>;
/**
 * save a graph to file
 * @param p a pointer -> graph
 */
void saveToFile(const shared_ptr<DGraph<int, int>> &p);
/**
 * read a graph from file
 * @param p a pointer -> graph
 */
void loadFromFile(shared_ptr<DGraph<int, int>> &p);

auto main() -> int
{
    const unsigned int initTableSize{20};
    std::vector<shared_ptr<DGraph<int, int>>> DGraphTable(initTableSize, nullptr);
    unsigned int curGraphIndex{1};
    unsigned int option{0};
    auto &curGraph = DGraphTable[curGraphIndex - 1];
    do
    {
        printMenu();
        std::cin >> option;
        if (option == 0U)
        {
            break;
        }
        try
        {
            switch (option)
            {
            case 1:
            {
                if (curGraph != nullptr)
                {
                    throw std::logic_error("[Error]: Graph has initialized before\n");
                }
                int size;
                std::cout << "Please enter the number of vertex" << std::endl;
                std::cin >> size;
                std::cout << "Please enter your vertex set like key<string> value<int>"
                          << std::endl;
                auto &&vList = readVex(std::cin, size);

                std::cout << "Please enter the number of edge" << std::endl;
                std::cin >> size;
                std::cout << "Please enter your edge set like from<string> to<string> value<int>"
                          << std::endl;
                auto &&eList = readEdge(std::cin, size);
                curGraph = make_shared<DGraph<int, int>>(DGraph<int, int>(vList, eList));
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            case 2:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Destory Graph " << curGraphIndex << std::endl;
                curGraph.reset();
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            case 3:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Please enter the key of the vertex to locate" << std::endl;
                string s;
                std::cin >> s;
                auto v = curGraph->locateVex(s);
                if (v == curGraph->getVListEnd())
                {
                    std::cout << "[Info]: vertex<" + s + "> does not exist" << std::endl;
                }
                else
                {
                    printVex<int, int>(*v);
                }
                break;
            }
            case 4:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Please enter the key and value to update" << std::endl;
                string key;
                int value;
                std::cin >> key >> value;
                curGraph->putVex(key, value);
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            case 5:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Please enter the key of the vertex" << std::endl;
                string s;
                std::cin >> s;
                auto v = curGraph->firstAdjVex(s);
                if (v == curGraph->getVListEnd())
                {
                    std::cout << "[Info]: vertex<" + s + "> does not have adj vertex" << std::endl;
                }
                else
                {
                    printVex(*v);
                }
                break;
            }
            case 6:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Please enter the key of the vertex and the key of relative vertex"
                          << std::endl;
                string k1;
                string k2;
                std::cin >> k1 >> k2;
                auto v = curGraph->nextAdjVex(k1, k2);
                if (v == curGraph->getVListEnd())
                {
                    std::cout << "[Info]: vertex<" + k1 +
                                     "> does not have adj vertex next to vertex<" + k2 + ">"
                              << std::endl;
                }
                else
                {
                    printVex(*v);
                }
                break;
            }
            case 7:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Please enter the key and the value of the vertex" << std::endl;
                Vertex<int, int> temp{"", 0};
                std::cin >> temp;
                curGraph->insertVex(std::move(temp));
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            case 8:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Please enter the key of the vertex to delete" << std::endl;
                string s;
                std::cin >> s;
                curGraph->deleteVex(s);
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            case 9:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Please enter the fromKey, toKey and info of the edge" << std::endl;
                Edge<int> temp{"", "", 0};
                std::cin >> temp;
                curGraph->insertEdge(std::move(temp));
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            case 10:
            {
                shouldInit<int, int>(curGraph);
                std::cout << "Please enter the fromKey and toKey of the edge" << std::endl;
                string k1;
                string k2;
                std::cin >> k1 >> k2;
                curGraph->deleteEdge(k1, k2);
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            case 11:
            {
                shouldInit<int, int>(curGraph);
                curGraph->DFSTraverse(printVex<int, int>);
                break;
            }
            case 12:
            {
                shouldInit<int, int>(curGraph);
                curGraph->BFSTraverse(printVex<int, int>);
                break;
            }
            case 13:
            {
                std::cout << "Please enter the index of graph to switch" << std::endl;
                unsigned int index;
                std::cin >> index;
                if (index < 1 || index > DGraphTable.size())
                {
                    throw std::out_of_range("[Error]: Index out of range!");
                }
                curGraph = DGraphTable[index - 1];
                curGraphIndex = index - 1;
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            case 14:
            {
                shouldInit<int, int>(curGraph);
                saveToFile(curGraph);
                std::cout << "[Success]: Save Graph " << curGraphIndex << " to file" << std::endl;
                break;
            }
            case 15:
            {
                loadFromFile(curGraph);
                std::cout << "[Success]: Done!" << std::endl;
                break;
            }
            default:
                break;
            }
        }
        catch (create_graph_error &msg)
        {
            curGraph.reset();
            std::cout << msg.what() << std::endl;
        }
        catch (std::out_of_range &msg)
        {
            std::cout << msg.what() << std::endl;
        }
        catch (std::logic_error &msg)
        {
            std::cout << msg.what() << std::endl;
        }
        getchar();
        getchar();
        system("clear");
    } while (option != 0U);
    std::cout << "Done!" << std::endl;
    return 0;
}

void printMenu()
{
    std::cout << "               Menu of Graph's options           \n"
                 "-------------------------------------------------\n"
                 "|                     0. exit                   |\n"
                 "|                                               |\n"
                 "|    1. CreateGraph        2. DestroyGraph      |\n"
                 "|    3. LocateVex          4. PutVex            |\n"
                 "|    5. FirstAdjVex        6. NextAdjVex        |\n"
                 "|    7. InsertVex          8. DeleteVex         |\n"
                 "|    9. InsertEdge         10. DeleteEdge       |\n"
                 "|    11. DFSTraverse       12. BFSTraverse      |\n"
                 "|    13. switchGraph       14. saveToFile       |\n"
                 "|    15. loadFromFile                           |\n"
                 "-------------------------------------------------\n"
              << std::endl;
}

template <typename V, typename E>
void printVex(const Vertex<V, E> &v)
{
    std::cout << v << std::endl;
}

auto readVex(std::istream &in, unsigned int size) -> list<Vertex<int, int>>
{
    list<Vertex<int, int>> vList;
    Vertex<int, int> temp{"", 0};
    for (int i = 0; i < size; i++)
    {
        in >> temp;
        vList.push_back(temp);
    }
    return vList;
}

auto readEdge(std::istream &in, unsigned int size) -> list<Edge<int>>
{
    list<Edge<int>> eList;
    Edge<int> temp{"", "", 0};
    for (int i = 0; i < size; i++)
    {
        in >> temp;
        eList.push_back(temp);
    }
    return eList;
}

void saveToFile(const shared_ptr<DGraph<int, int>> &p)
{
    std::vector<string> sv;
    std::ofstream outFile;
    outFile.open("./graph.txt", std::ios::out);
    outFile << p->getVexNum() << std::endl;
    std::for_each(p->getVListBeg(), p->getVListEnd(), [&outFile, &sv](const Vertex<int, int> &v) {
        outFile << v.getKey() << " " << v.getInfo() << std::endl;
        std::for_each(v.getEListBeg(), v.getEListEnd(), [&sv](const Edge<int> &e) {
            sv.push_back(e.getFrom() + " " + e.getTo() + " " + std::to_string(e.getInfo()));
        });
    });
    outFile << p->getEdgeNum() << std::endl;
    std::for_each(sv.begin(), sv.end(), [&outFile](const string &s) { outFile << s << std::endl; });
}

void loadFromFile(shared_ptr<DGraph<int, int>> &p)
{
    std::ifstream inFile;
    inFile.open("./graph.txt", std::ios::in);
    unsigned int size;
    inFile >> size;
    auto &&vList = readVex(inFile, size);
    inFile >> size;
    auto &&eList = readEdge(inFile, size);
    p = make_shared<DGraph<int, int>>(DGraph<int, int>(vList, eList));
}