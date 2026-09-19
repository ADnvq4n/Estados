#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Node.hpp"

class Grid
{
private:
    int filas;
    int columnas;

    float tamanoCelda;

    float offsetX;
    float offsetY;

    std::vector<std::vector<Node>> nodos;

    sf::Texture texturaObstaculo;

public:
    Grid(
        int filas,
        int columnas,
        float tamanoCelda,
        float offsetX,
        float offsetY
    );

    Node& getNodo(
        int fila,
        int columna
    );

    int getFilas() const;
    int getColumnas() const;

    bool esValida(
        int fila,
        int columna
    ) const;

    void alternarObstaculo(
        int fila,
        int columna
    );

    void dibujar(
        sf::RenderWindow& ventana,
        const std::vector<Node*>& camino,
        Node* inicio,
        Node* destino
    );

    float getTamanoCelda() const;
    float getOffsetX() const;
    float getOffsetY() const;
};

#endif
