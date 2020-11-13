/**
 * @file vertex.h
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
#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class Vertex
{
private:
    string label;
public:
    Vertex(string name);
    vector<shared_ptr<Vertex>> connections;

    string getName(){ return this->label; }
    void addConnection(Vertex who);
    bool operator==(Vertex thatguy){ return thatguy.label == this->label; }
    void printNeighborhood();
};

/**
 * @brief Construct a new Vertex:: Vertex object
 * 
 * @param name 
 */
Vertex::Vertex(string name){
    this->label = name;
}

/**
 * @brief Adds who as a connection in this vertex
 * 
 * @param who A pointer to a Vertex object
 */
void Vertex::addConnection(Vertex who){
    shared_ptr<Vertex> neighbor = make_shared<Vertex>(who);
    this->connections.push_back(neighbor);
}

void Vertex::printNeighborhood(){
    vector<shared_ptr<Vertex>>::iterator it;

    for(it=this->connections.begin(); it!=this->connections.end(); it++){
        cout << (*it)->getName() << " ";
    }
}