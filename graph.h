/**
 * @file graph.h
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
#include "Vertex.h"
#include <algorithm>
#include <list>

using namespace std;

class Graph
{
private:
    vector<Vertex> vertices; // Container for vertices as lists of connections
public:
    Graph(vector<string> labels);
    void addEdge(string u, string v);
    int getSize(){ return this->vertices.size(); }
    void printGraph();
    Vertex* getNode(string);
    void BFS(Vertex*); 
    void DFS(Vertex*); 
};

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param labels 
 */
Graph::Graph(vector<string> labels){
    vector<string>::iterator it;

    for(it=labels.begin(); it!=labels.end(); it++){
        Vertex newboy = Vertex(*it);
        this->vertices.push_back(newboy);
    }
}

/**
 * @brief Adds an edge between two vertices
 * 
 * @param u A string representing the label of a vertex
 * @param v A string representing the label of a vertex
 */
void Graph::addEdge(string u, string v){
    vector<Vertex>::iterator pu, pv;
    pu = find(this->vertices.begin(), this->vertices.end(), u);
    pv = find(this->vertices.begin(), this->vertices.end(), v);

    if (pu == this->vertices.end() && pv == this->vertices.end()){
        // if they don't exist, add them
        auto U = make_shared<Vertex>(u); // this generates a shared_ptr
        auto V = make_shared<Vertex>(v); // this also generates a shared_ptr
        U->addConnection(*V);
        V->addConnection(*U);
        this->vertices.push_back(*U);
        this->vertices.push_back(*V);

    }
    else if(pv == this->vertices.end()){
        //only pu exists, so create pv and find U
        Vertex* U = &(*pu);  // this generates a normal pointer to the object at pu, which is scope-dependent
        auto V = make_shared<Vertex>(v);  // this generates a shared_ptr since it's being created (happens only once)
        U->addConnection(*V);
        V->addConnection(*U);
        this->vertices.push_back(*V);
    }
    else if(pu == this->vertices.end()){
        //only pv exists, so add pu and find V
        auto U = make_shared<Vertex>(u); // this generates a shared_ptr since it's being created (happens only once)
        Vertex* V = &(*pv);  // this generates a normal pointer to the object at pv, which is scope-dependent
        U->addConnection(*V);
        V->addConnection(*U);
        this->vertices.push_back(*U);
    }
    else{
        //both exist, so find them both
        // these two generate a normal pointer to the object at pu and pv, which is scope-dependent
        Vertex* U = &(*pu); 
        Vertex* V = &(*pv);
        U->addConnection(*V);
        V->addConnection(*U);
    }
}
/**
 * @brief Prints the graph by adjacency lists
 * 
 */

void Graph::printGraph(){
    vector<Vertex>::iterator it;

    for(it=this->vertices.begin(); it!=this->vertices.end(); it++){
        Vertex current = *it;
        cout << current.getName() << " has the following connections: [";
        //each vertex prints its neighbors
        current.printNeighborhood();
        cout << "]" << endl;
    }
}

/**
 * @brief Get a node
 * 
 * @param myVertex 
 * @return vertexSearched* 
 */
Vertex* Graph::getNode(string myVertex)
{
    Vertex* vertexSearched;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].getName() == myVertex)
        {
            vertexSearched = &vertices[i];
        }
    }
    return vertexSearched;
}

/**
 * @brief Iterate and print nodes with a BFS walkthrough
 * 
 * @param vertice 
 * 
 * Complexity: O(n)
 */
void Graph::BFS(Vertex* vertice) 
{ 
    //vector<shared_ptr<Vertex>> visited;
    //list<shared_ptr<Vertex>> queue;
    vector<Vertex> visited;
    list<Vertex> queue;
    auto newVertice (*vertice); 

    visited.push_back(newVertice);
    queue.push_back(newVertice);

    while (!queue.empty()) {
        Vertex currVertex = queue.front();
        queue.pop_front();

        for (int iK = 0; iK < currVertex.connections.size(); ++iK) {
            bool myFlag = false; 
            for (int i = 0; i < visited.size(); i++)
            {
                if (*currVertex.connections[iK] == visited[i])
                {
                    myFlag = true; 
                    break; 
                }
            }
            if (myFlag == false)
            {
                queue.push_back(*currVertex.connections[iK]);
                visited.push_back(*currVertex.connections[iK]);
            }
        }
        cout << currVertex.getName() << " ";
    }
}

/**
 * @brief Iterate and print nodes with a DFS walkthrough
 * 
 * @param vertice 
 * 
 * Complexity: O(n)
 */
void Graph::DFS(Vertex* vertice) 
{ 
    vector <Vertex> stack;
    vector <Vertex> visited; 
    auto newVertice (*vertice); 

    stack.push_back(newVertice); 
    visited.push_back(newVertice);

    while (!stack.empty())
    {
        Vertex currVertex = stack[stack.size() - 1];
        stack.pop_back();
        for (int iK = 0; iK < currVertex.connections.size(); iK++)
        {
            bool myFlag = false;
            for (int i = 0; i < visited.size(); i++)
            {
                if (*currVertex.connections[iK] == visited[i])
                {
                    myFlag = true; 
                    break; 
                }
            }
            if (myFlag == false)
            {
                stack.push_back(*currVertex.connections[iK]);
                visited.push_back(*currVertex.connections[iK]);
            }
        }
        cout << currVertex.getName() << " "; 
    }
    
} 
