#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>

#include "Node.hpp"
#include "Grid.hpp"

class AStar
{
private:
    float calcularHeuristica(
        Node* actual,
        Node* destino
    );

public:
    AStar();

    std::vector<Node*> encontrarCamino(
        Grid& grid,
        Node* inicio,
        Node* destino
    );
};

#endif