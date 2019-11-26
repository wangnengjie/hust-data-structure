#include "DGraph.hh"
#include <iostream>
#include <memory>

#define INITIAL_TABLE_SIZE

using std::make_shared;
using std::shared_ptr;

void printVex(const Vertex<string, string> &v);
void printMenu();

auto main() -> int
{
    unsigned int tableSize{INITIAL_TABLE_SIZE};
    std::vector<shared_ptr<DGraph<int, int>>> DGraphTable(tableSize, nullptr);
    unsigned int curGraph{0};
    unsigned int option{0};
    do
    {
        printMenu();
        std::cin >> option;
        std::cin.sync();
        try
        {
            switch (option)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                std::cout << "Destory Graph " << curGraph << std::endl;
                DGraphTable[curGraph].reset();
                std::cout << "[Info]: Success" << std::endl;
                break;
            }
        }
        catch (create_graph_error &msg)
        {
            DGraphTable[curGraph].reset();
            std::cout << msg.what() << std::endl;
        }
        catch (std::logic_error &msg)
        {
            std::cout << msg.what() << std::endl;
        }
    } while (option != 0U);
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
                 "|    9. InsertArc          10. DeleteArc        |\n"
                 "|    11. DFSTraverse       12. BFSTraverse      |\n"
                 "|    13. switchGraph       14. saveToFile       |\n"
                 "|    15. loadFromFile                           |\n"
                 "-------------------------------------------------\n\n"
              << std::endl;
}

void printVex(const Vertex<string, string> &v) { std::cout << v << std::endl; }
