#include <iostream>
#include "graph.h"

void ejemplo_1() {
    utec::graph<char, int, int> g1;
    // Crear vertices
    g1.push_vertex('A', 10);
    g1.push_vertex('B', 20);
    g1.push_vertex('C', 50);
    g1.push_vertex('D', 30);
    // Crear aristas
    g1.push_edge({'A','B', 1});
    g1.push_edge({'A','C', 4});
    g1.push_edge({'A','D', 3});
    g1.push_edge({'C','D', 6});
    // Retornar los valores de los vertices
    std::cout << g1.get_vertex('A') << std::endl;
    std::cout << g1.get_vertex('C') << std::endl;
    // Retornar los pesos de la aristas
    std::cout << g1.get_edge('A', 'B') << std::endl;
    std::cout << g1.get_edge('C', 'A') << std::endl;
    std::cout << g1.get_edge('D', 'B') << std::endl;

    g1.bfs('A', [](auto item) {
        std::cout << item.first << " " << item.second << std::endl;
    });


}

int main() {
    ejemplo_1();
    return 0;
}
