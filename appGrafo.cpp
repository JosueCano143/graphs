/**
 * @file appGrafo.cpp
 * @authors
 *  Carolina Gómez Manzano                  A01632229
 *  Alejandra Guadalupe Olivas Altamirano   A01741389
 *  Josue Salvador Cano Martinez            A00829022
 * @brief 
 * @version 0.1
 * @date 2020-11-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "graph.h"

/**
 * @brief Application of the created classes
 * 
 * @return nothing
 */
int main() 
{
    vector<string> V = {"A", "B", "C", "D"};
    Graph graph = Graph(V);
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");
    graph.addEdge("C", "A");
    graph.addEdge("D", "C");


    graph.printGraph();

    int option; 
    do {
        cout << endl; 
        cout << "Se considera el nodo con valor 'A' como la raiz" << endl; 
        cout << "1. Depth First Search" << endl;
        cout << "2. Breadth First Search" << endl; 
        cout << "3. Salir" << endl; 
        cin >> option; 
   
        switch (option) {
            case 1:
                graph.DFS(graph.getNode("A"));
                break;

            case 2:
                graph.BFS(graph.getNode("A"));
                break;
        }
    } while (option != 3);

    return 0; 
}