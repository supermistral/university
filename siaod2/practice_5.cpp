#include <iostream>
#include <vector>
#include <iomanip>

typedef std::vector<std::vector<int>> matrix;

const int INF = INT_MAX;


matrix createGraph(matrix&);
matrix floydWarshallDistance(matrix, matrix&);
void printDistance(matrix);
void printPath(matrix, matrix, int, int);
void run();


int main()
{
    run();
    return 0;
}

// создание графа
matrix createGraph(matrix& pointsPath) {
    int u, v, weight, n;
    std::cin >> n;

    matrix graph(n, std::vector<int>(n));       // матрица смежности
    pointsPath.assign(n, std::vector<int>(n));  // матрица вершин

    while (1) {
        std::cin >> u;              // ввод вершины
        if (u == 0) {
            return graph;
        }
        std::cin >> v >> weight;    // ввод вершины и веса

        graph[u - 1][v - 1] = weight;
        pointsPath[u - 1][v - 1] = graph[u - 1][v - 1] == 0 ? -1 : v - 1;   
            // uv элемент = v, если есть ребро
    }

    return graph;
}

// алгоритм Флойда-Уоршелла
matrix floydWarshallDistance(matrix graph, matrix& pointsPath) {
    int n = graph.size();
    matrix distance = graph;

    for (int i = 0; i < n; ++i) {           // начальная инициализация
        for (int j = 0; j < n; ++j) {
            if (distance[i][j] == 0 && i != j) {    // если ребра нет, расстояние = +inf
                distance[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (    // если путь на текущей итерации кратчайший
                    distance[u][i] != INF && distance[i][v] != INF &&
                    distance[u][v] > (distance[u][i] + distance[i][v])
                ) {
                    distance[u][v] = distance[u][i] + distance[i][v];   // обновить расстояние
                                                            // обновить вершину для пути из u в v
                    pointsPath[u][v] = pointsPath[u][i];    // чтобы пройти u -> v, нужно пройти через
                }                                           //   кратчайший путь u -> i
            }
        }
    }

    return distance;
}

// вывод матрицы кратчайших расстояний
void printDistance(matrix distance) {
    int n = distance.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::left << std::setw(4);
            if (distance[i][j] == INF) {
                std::cout << "INF";
            }
            else {
                std::cout << distance[i][j];
            }
        }
        std::cout << "\n";
    }
}

// вывод пути между вершинами по матрице вершин
void printPath(matrix dist, matrix pointPath, int u, int v) {
    int n = pointPath.size();
    
    std::cout << "Shortest path from " << u << " to " << v;
    --u; --v;

    if (dist[u][v] == INF) {        // пути не существует
        std::cout << " doesn't exist\n";
        return;
    }

    std::cout << " = " << dist[u][v] << " | " << u + 1;
    while (u != v) {                // перемещение по столбцу v матрицы вершин
        u = pointPath[u][v];
        std::cout << " -> " << u + 1;
    }
    std::cout << "\n";
}

void run() {
    std::string command;
    matrix pointsPath, G, dist;
    int u, v;
    
    std::cout << "Work with graph\n---------------\n"
        << "create <amount of edges>\n"
        << "distance-matrix\n"
        << "path <edge from> <edge to>\n"
        << "q (exit)\n"
        << "---------------\n\n";

    while (1) {
        std::cin >> command;

        if (command == "create") {
            G = createGraph(pointsPath);
            dist = floydWarshallDistance(G, pointsPath);
        }
        else if (command == "distance-matrix") {
            printDistance(dist);
        }
        else if (command == "path") {
            std::cin >> u >> v;
            printPath(dist, pointsPath, u, v);
        }
        else if (command == "q") {
            break;
        }
        else {
            std::cout << "No such command\n";
        }
        std::cout << "\n";
    }
}
