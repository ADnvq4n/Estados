#include "../include/Grid.hpp"

#include <iostream>

Grid::Grid(
    int filas,
    int columnas,
    float tamanoCelda,
    float offsetX,
    float offsetY
)
{
    this->filas = filas;
    this->columnas = columnas;
    this->tamanoCelda = tamanoCelda;

    this->offsetX = offsetX;
    this->offsetY = offsetY;

    // =========================================
    // CARGAR TEXTURA DE OBSTACULO
    // =========================================

    if (!texturaObstaculo.loadFromFile(
            "assets/obstaculo.png"))
    {
        std::cerr
            << "ERROR: No se pudo cargar "
            << "obstaculo.png"
            << std::endl;
    }
    else
    {
        std::cout
            << "Obstaculo cargado correctamente"
            << std::endl;
    }

    // =========================================
    // CREAR NODOS
    // =========================================

    nodos.resize(filas);

    for (int fila = 0;
         fila < filas;
         fila++)
    {
        nodos[fila].reserve(columnas);

        for (int columna = 0;
             columna < columnas;
             columna++)
        {
            nodos[fila].emplace_back(
                fila,
                columna
            );
        }
    }
}

// =============================================
// OBTENER NODO
// =============================================

Node& Grid::getNodo(
    int fila,
    int columna
)
{
    return nodos[fila][columna];
}

// =============================================
// OBTENER NUMERO DE FILAS
// =============================================

int Grid::getFilas() const
{
    return filas;
}

// =============================================
// OBTENER NUMERO DE COLUMNAS
// =============================================

int Grid::getColumnas() const
{
    return columnas;
}

// =============================================
// COMPROBAR SI UNA POSICION ES VALIDA
// =============================================

bool Grid::esValida(
    int fila,
    int columna
) const
{
    return fila >= 0 &&
           fila < filas &&
           columna >= 0 &&
           columna < columnas;
}

// =============================================
// ACTIVAR / DESACTIVAR OBSTACULO
// =============================================

void Grid::alternarObstaculo(
    int fila,
    int columna
)
{
    if (!esValida(fila, columna))
    {
        return;
    }

    Node& nodo =
        nodos[fila][columna];

    nodo.setObstaculo(
        !nodo.esObstaculo()
    );
}

// =============================================
// OBTENER TAMAÑO DE CELDA
// =============================================

float Grid::getTamanoCelda() const
{
    return tamanoCelda;
}

// =============================================
// OBTENER OFFSET X
// =============================================

float Grid::getOffsetX() const
{
    return offsetX;
}

// =============================================
// OBTENER OFFSET Y
// =============================================

float Grid::getOffsetY() const
{
    return offsetY;
}

// =============================================
// DIBUJAR GRID
// =============================================

void Grid::dibujar(
    sf::RenderWindow& ventana,
    const std::vector<Node*>& camino,
    Node* inicio,
    Node* destino
)
{
    for (int fila = 0;
         fila < filas;
         fila++)
    {
        for (int columna = 0;
             columna < columnas;
             columna++)
        {
            Node& nodo =
                nodos[fila][columna];

            // =================================
            // POSICION DE LA CELDA
            // =================================

            float x =
                offsetX +
                columna * tamanoCelda;

            float y =
                offsetY +
                fila * tamanoCelda;

            // =================================
            // OBSTACULO
            // =================================

            if (nodo.esObstaculo())
            {
                sf::Sprite obstaculo;

                obstaculo.setTexture(
                    texturaObstaculo
                );

                obstaculo.setPosition(
                    x,
                    y
                );

                if (
                    texturaObstaculo
                        .getSize()
                        .x > 0 &&

                    texturaObstaculo
                        .getSize()
                        .y > 0
                )
                {
                    obstaculo.setScale(
                        tamanoCelda /
                            texturaObstaculo
                                .getSize()
                                .x,

                        tamanoCelda /
                            texturaObstaculo
                                .getSize()
                                .y
                    );
                }

                ventana.draw(
                    obstaculo
                );

                continue;
            }

            // =================================
            // CELDA DEL TABLERO
            // =================================

            sf::RectangleShape celda;

            celda.setSize(
                sf::Vector2f(
                    tamanoCelda,
                    tamanoCelda
                )
            );

            celda.setPosition(
                x,
                y
            );

            // =================================
            // COLOR BASE
            // NEGRO
            // =================================

            celda.setFillColor(
                sf::Color::Black
            );

            // =================================
            // BORDE BLANCO
            // =================================

            celda.setOutlineThickness(
                1.0f
            );

            celda.setOutlineColor(
                sf::Color::White
            );

            // =================================
            // CAMINO A*
            // =================================

            for (Node* paso : camino)
            {
                if (paso == &nodo)
                {
                    celda.setFillColor(
                        sf::Color(80, 140, 255)
                    );

                    break;
                }
            }

            // =================================
            // INICIO
            // =================================

            if (inicio == &nodo)
            {
                celda.setFillColor(
                    sf::Color::Green
                );
            }

            // =================================
            // DESTINO
            // =================================

            if (destino == &nodo)
            {
                celda.setFillColor(
                    sf::Color::Red
                );
            }

            // =================================
            // DIBUJAR CELDA
            // =================================

            ventana.draw(
                celda
            );
        }
    }
}