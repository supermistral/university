#include <iostream>
#include <vector>
#include <iomanip>


typedef std::vector<std::string> Colors;


Colors COLORS = {
        "RED", "GREEN", "YELLOW", "BLUE", "WHITE", "PURPLE", "ORANGE"
};


class Graph {

    std::vector<std::vector<int>> adjList;      // массив списков смежности

public:
    Graph() {}

    Graph(int size) {
        for (int i = 0; i < size; ++i) {
            adjList.push_back(std::vector<int>());
        }
    }

    Graph(int size, std::vector<std::vector<int>> edges) {
        for (int i = 0; i < size; ++i) {
            adjList.push_back(std::vector<int>());
        }

        for (size_t i = 0; i < edges.size(); ++i) {
            add(edges[i][0], edges[i][1]);
        }
    }

    void add(int u, int v) {
        adjList[u].push_back(v);
    }

    int* colorsGreedy() {
        const int size = adjList.size();
        int *colors = new int[size];            // i-ое число - цвет вершины i
        bool *availability = new bool[size];    // i-ый элемент - доступность цвета

        colors[0] = 0;
        for (int i = 1; i < size; ++i) {
            colors[i] = -1;     // изначально цвет не задан
        }

        for (int i = 0; i < size; ++i) {
            availability[i] = true;     // изначально все цвета доступны
        }

        int availableColor;

        for (int edge = 1; edge < size; ++edge) {
            for (int adjEdge : adjList[edge]) {
                if (colors[adjEdge] != -1) {                // если цвет задан
                    availability[colors[adjEdge]] = false;  // пометить как недоступный
                }
            }

            for (int color = 0; color < size; ++color) {    // поиск свободного цвета
                if (availability[color]) {
                    availableColor = color;
                    break;
                }
            }

            colors[edge] = availableColor;      // задать цвет вершине

            for (int adjEdge : adjList[edge]) {         // вернуть доступность
                if (colors[adjEdge] != -1) {            //   в исходное состояние
                    availability[colors[adjEdge]] = true;
                }
            }
        }

        std::cout << "\nDigraph {\nnode[style=filled]";         // DOT-нотация с цветами
        for (int i = 0; i < size; ++i) {
            std::cout << "\n" << i + 1 << "[color=" << COLORS[colors[i]] << "]";
            for (int edge : adjList[i]) {
                std::cout << "\n" << i + 1 << " -> " << edge + 1;
            }
        }
        std::cout << "\n}";

        delete[] availability;

        return colors;
    }

    int* colorsBruteforce() {
        const int size = adjList.size();
        int* colors = new int[size] { 0 };

        int ind = 0;
        int limit = 1;
        bool flag;

        while (colors[size - 1] < size - 1) {               // прямой перебор вариантов
            if (ind == size - 1 && colors[ind] == limit)
                ++limit;

            ind = 0;

            while (colors[ind] == limit) {      // сначала перебирается 1-й, потом менятся
                colors[ind] = 0;                //   2-й и вновь сначала и до последнего
                ++ind;
            }

            ++colors[ind];

            for (int edge = 0; edge < size; ++edge) {       // проверка на корректность
                flag = false;

                for (int adjEdge : adjList[edge]) {
                    if (colors[edge] == colors[adjEdge]) {
                        flag = true;
                        break;
                    }
                }

                if (flag) 
                    break;
            }

            if (!flag) {        // флаг = false => цвета корректны
                break;
            }
        }

        std::cout << "\nDigraph {\nnode[style=filled]";         // DOT-нотация с цветами
        for (int i = 0; i < size; ++i) {
            std::cout << "\n" << i + 1 << "[color=" << COLORS[colors[i]] << "]";
            for (int edge : adjList[i]) {
                std::cout << "\n" << i + 1 << " -> " << edge + 1;
            }
        }
        std::cout << "\n}";

        return colors;
    }
};


class Crossroads {

    struct Edge {
        char from, to;
    };

    Graph graph;
    std::vector<Edge> tableEdges;   // таблица соотвествия: i-ая вершина
                                    //   обозначает дорогу перекрестка

    int findEdge(int from, int to) {
        for (size_t i = 0; i < tableEdges.size(); ++i) {
            if (tableEdges[i].from == from && tableEdges[i].to == to) {
                return i;
            }
        }
        return -1;
    }

public:

    void input() {
        char from = 1, to;
        int dir;

        std::cout << "\nInput parts of crossroads: <from> <to> <direction>"
            << "\nfrom <- to = -1"
            << "\nfrom <-> to = 0"
            << "\nfrom -> to = 1"
            << "\n0 - end of input"
            << "\n----------------\n";

        while (1) {     // пока не введен 0
            std::cout << "from - to - dir : "; 
            std::cin >> from;
            
            if (from == '0') {
                break;
            }

            std::cin >> to >> dir;

            if (dir >= 0) {
                tableEdges.push_back({ from, to });
                if (dir == 0) {
                    tableEdges.push_back({ to, from });
                }
            }
            else {
                tableEdges.push_back({ to, from });
            }
        }

        std::vector<std::vector<int>> incompatibleEdges;
        int foundEdge;

        std::cout << "\n\nIncompatible turns for routes\n";

        for (int i = 0; i < tableEdges.size(); ++i) {
            std::cout << tableEdges[i].from << " -> " << tableEdges[i].to << " : ";
            while (1) {
                std::cin >> from;
                if (from == '0')
                    break;
                std::cin >> to;

                foundEdge = findEdge(from, to);
                if (foundEdge >= 0) {
                    incompatibleEdges.push_back({ i, foundEdge });
                }
            }
        }

        graph = Graph(tableEdges.size(), incompatibleEdges);
    }

    void solve(Colors colors, int* colorIndices) {
        int size = tableEdges.size();
        int colorsSize = colors.size();

        std::vector<std::vector<Edge>> colorsEdges(colorsSize);

        for (int i = 0; i < size; ++i) {
            if (colorIndices[i] >= colorsSize) {
                std::cout << "\nNot enough colors";
                delete[] colorIndices;
                return;
            }
            colorsEdges[colorIndices[i]].push_back(tableEdges[i]);
        }

        std::cout << "\n";
        for (int i = 0; i < colorsSize; ++i) {
            std::cout << "\n" << std::setw(10) << std::left << colors[i] << " : ";
            for (Edge edge : colorsEdges[i]) {
                std::cout << edge.from << edge.to << " ";
            }
        }

        delete[] colorIndices;
    }

    void solveGreedy(Colors colors) {
        int* colorIndices = graph.colorsGreedy();
        solve(colors, colorIndices);
    }

    void solveBruteforce(Colors colors) {
        int* colorIndices = graph.colorsBruteforce();
        solve(colors, colorIndices);
    }
};


void testColorGraph() {
    int size, from, to;

    std::cout << "\nGraph size = ";
    std::cin >> size;

    std::vector<std::vector<int>> edges;
    Graph graph(size);

    std::cout << "\nFrom - to"
        << "\n0 - end of the input"
        << "\n--------------------\n";

    while (1) {
        std::cin >> from;
        if (from == 0)
            break;
        std::cin >> to;
        graph.add(from - 1, to - 1);
    }

    graph.colorsGreedy();
    graph.colorsBruteforce();
}


int main()
{
    Crossroads crossroads;

    crossroads.input();

    crossroads.solveGreedy(COLORS);
    //crossroads.solveBruteforce(COLORS);

    //testColorGraph();

    return 0;
}

// Testing
/*

A B 0
A C 1
A D 0
A E -1
B C 1
B D 0
B E -1
C D -1
C E -1
D E -1
0
BC BD DA EA 0
0
BD DA DB EA EB 0
EA EB EC 0
AB AC BD EB EC 0
AB AC AD 0
AB DB EB 0
AB AC DA EB EC 0
AC BC EC 0
AC AD BC BD DA 0
0
AD BD DA DB 0
0


5
1 5
5 1
5 3
3 5
5 4
4 5
4 2
2 4
3 2
2 3
0

*/
