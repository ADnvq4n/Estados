#include "../include/AStar.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

AStar::AStar()
{
}

float AStar::calcularHeuristica(
    Node* actual,
    Node* destino
)
{
    float diferenciaFila =
        static_cast<float>(
            std::abs(
                actual->getFila() -
                destino->getFila()
            )
        );

    float diferenciaColumna =
        static_cast<float>(
            std::abs(
                actual->getColumna() -
                destino->getColumna()
            )
        );

    return diferenciaFila + diferenciaColumna;
}

std::vector<Node*> AStar::encontrarCamino(
    Grid& grid,
    Node* inicio,
    Node* destino
)
{
    std::vector<Node*> camino;

    if (inicio == nullptr || destino == nullptr)
    {
        return camino;
    }

    if (inicio->esObstaculo() || destino->esObstaculo())
    {
        return camino;
    }

    std::vector<Node*> abiertos;
    std::vector<Node*> cerrados;

    // Reiniciar los valores de todos los nodos
    for (int fila = 0; fila < grid.getFilas(); fila++)
    {
        for (int columna = 0;
             columna < grid.getColumnas();
             columna++)
        {
            Node& nodo = grid.getNodo(fila, columna);

            nodo.setG(
                std::numeric_limits<float>::infinity()
            );

            nodo.setH(0.0f);
            nodo.calcularF();
            nodo.setPadre(nullptr);
        }
    }

    // El nodo inicial comienza con costo 0
    inicio->setG(0.0f);

    // Calculamos su heurística
    inicio->setH(
        calcularHeuristica(inicio, destino)
    );

    // f = g + h
    inicio->calcularF();

    // Agregamos el inicio a OPEN
    abiertos.push_back(inicio);

    while (!abiertos.empty())
    {
        // ==========================================
        // BUSCAR EL NODO CON EL MENOR F
        // ==========================================

        Node* actual = abiertos[0];

        for (Node* nodo : abiertos)
        {
            if (nodo->getF() < actual->getF())
            {
                actual = nodo;
            }
        }

        // ==========================================
        // ¿LLEGAMOS AL DESTINO?
        // ==========================================

        if (actual == destino)
        {
            Node* nodoActual = destino;

            while (nodoActual != nullptr)
            {
                camino.push_back(nodoActual);
                nodoActual = nodoActual->getPadre();
            }

            std::reverse(
                camino.begin(),
                camino.end()
            );

            return camino;
        }

        // ==========================================
        // MOVER ACTUAL DE OPEN A CLOSED
        // ==========================================

        abiertos.erase(
            std::remove(
                abiertos.begin(),
                abiertos.end(),
                actual
            ),
            abiertos.end()
        );

        cerrados.push_back(actual);

        // ==========================================
        // REVISAR LOS 4 VECINOS
        // ==========================================

        const int movimientos[4][2] =
        {
            {-1, 0}, // Arriba
            {1, 0},  // Abajo
            {0, -1}, // Izquierda
            {0, 1}   // Derecha
        };

        for (int i = 0; i < 4; i++)
        {
            int nuevaFila =
                actual->getFila() +
                movimientos[i][0];

            int nuevaColumna =
                actual->getColumna() +
                movimientos[i][1];

            // Comprobar que la posición existe
            if (!grid.esValida(
                    nuevaFila,
                    nuevaColumna))
            {
                continue;
            }

            Node* vecino =
                &grid.getNodo(
                    nuevaFila,
                    nuevaColumna
                );

            // Ignorar obstáculos
            if (vecino->esObstaculo())
            {
                continue;
            }

            // Ignorar nodos que ya fueron revisados
            if (std::find(
                    cerrados.begin(),
                    cerrados.end(),
                    vecino
                ) != cerrados.end())
            {
                continue;
            }

            // ==========================================
            // CALCULAR NUEVO COSTO G
            // ==========================================

            float nuevoG =
                actual->getG() + 1.0f;

            // ==========================================
            // ¿ES UN CAMINO MEJOR?
            // ==========================================

            bool estaEnAbiertos =
                std::find(
                    abiertos.begin(),
                    abiertos.end(),
                    vecino
                ) != abiertos.end();

            if (!estaEnAbiertos ||
                nuevoG < vecino->getG())
            {
                vecino->setG(nuevoG);

                vecino->setH(
                    calcularHeuristica(
                        vecino,
                        destino
                    )
                );

                vecino->calcularF();

                vecino->setPadre(actual);

                if (!estaEnAbiertos)
                {
                    abiertos.push_back(vecino);
                }
            }
        }
    }

    // No se encontró ningún camino
    return camino;
}