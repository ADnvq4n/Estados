#include <SFML/Graphics.hpp>

#include "../include/Grid.hpp"
#include "../include/AStar.hpp"

int main()
{
    const int filas = 20;
    const int columnas = 20;
    const float tamanoCelda = 30.0f;

    // =============================================
    // CREAR VENTANA
    // =============================================
    sf::RenderWindow ventana(
        sf::VideoMode(600, 600),
        "A* PathFinding"
    );

    // =============================================
    // CREAR GRID
    // =============================================
    Grid grid(
        filas,
        columnas,
        tamanoCelda
    );

    // =============================================
    // CREAR ALGORITMO A*
    // =============================================
    AStar algoritmo;

    // =============================================
    // VARIABLES DEL CAMINO
    // =============================================
    std::vector<Node*> camino;

    Node* inicio = nullptr;
    Node* destino = nullptr;

    // =============================================
    // CONTROL DEL MOUSE
    // =============================================
    bool clicIzquierdoAnterior = false;
    bool clicDerechoAnterior = false;

    // =============================================
    // MODO DE OBSTÁCULOS
    // false = modo normal
    // true  = modo obstáculos
    // =============================================
    bool modoObstaculos = false;

    // =============================================
    // BUCLE PRINCIPAL
    // =============================================
    while (ventana.isOpen())
    {
        sf::Event evento;

        // =========================================
        // EVENTOS
        // =========================================
        while (ventana.pollEvent(evento))
        {
            // -------------------------------------
            // CERRAR VENTANA
            // -------------------------------------
            if (evento.type == sf::Event::Closed)
            {
                ventana.close();
            }

            // -------------------------------------
            // TECLAS
            // -------------------------------------
            if (evento.type == sf::Event::KeyPressed)
            {
                // =================================
                // TECLA O
                // ACTIVAR/DESACTIVAR OBSTÁCULOS
                // =================================
                if (evento.key.code == sf::Keyboard::O)
                {
                    modoObstaculos =
                        !modoObstaculos;

                    // Borrar camino anterior
                    camino.clear();

                    if (modoObstaculos)
                    {
                        ventana.setTitle(
                            "A* PathFinding - MODO OBSTACULOS"
                        );
                    }
                    else
                    {
                        ventana.setTitle(
                            "A* PathFinding - MODO NORMAL"
                        );
                    }
                }

                // =================================
                // TECLA ESPACIO
                // EJECUTAR A*
                // =================================
                if (evento.key.code == sf::Keyboard::Space)
                {
                    if (inicio != nullptr &&
                        destino != nullptr)
                    {
                        camino =
                            algoritmo.encontrarCamino(
                                grid,
                                inicio,
                                destino
                            );

                        if (camino.empty())
                        {
                            ventana.setTitle(
                                "A* PathFinding - SIN CAMINO"
                            );
                        }
                        else
                        {
                            ventana.setTitle(
                                "A* PathFinding - CAMINO ENCONTRADO"
                            );
                        }
                    }
                    else
                    {
                        ventana.setTitle(
                            "A* PathFinding - FALTA INICIO O DESTINO"
                        );
                    }
                }
            }
        }

        // =============================================
        // ESTADO ACTUAL DEL MOUSE
        // =============================================
        bool clicIzquierdo =
            sf::Mouse::isButtonPressed(
                sf::Mouse::Left
            );

        bool clicDerecho =
            sf::Mouse::isButtonPressed(
                sf::Mouse::Right
            );

        // =============================================
        // POSICIÓN DEL MOUSE
        // =============================================
        sf::Vector2i posicionMouse =
            sf::Mouse::getPosition(ventana);

        // =============================================
        // CONVERTIR POSICIÓN DEL MOUSE
        // A FILA Y COLUMNA
        // =============================================
        int columna =
            static_cast<int>(
                posicionMouse.x / tamanoCelda
            );

        int fila =
            static_cast<int>(
                posicionMouse.y / tamanoCelda
            );

        // =============================================
        // CLIC IZQUIERDO
        // =============================================
        if (clicIzquierdo &&
            !clicIzquierdoAnterior)
        {
            if (grid.esValida(fila, columna))
            {
                // -------------------------------------
                // MODO OBSTÁCULOS
                // -------------------------------------
                if (modoObstaculos)
                {
                    grid.alternarObstaculo(
                        fila,
                        columna
                    );

                    // Si cambiamos obstáculos,
                    // el camino anterior deja de ser válido.
                    camino.clear();
                }
                else
                {
                    // ---------------------------------
                    // SELECCIONAR INICIO
                    // ---------------------------------
                    Node& nodo =
                        grid.getNodo(
                            fila,
                            columna
                        );

                    // El inicio no puede ser obstáculo
                    if (!nodo.esObstaculo())
                    {
                        inicio = &nodo;

                        // Borrar camino anterior
                        camino.clear();
                    }
                }
            }
        }

        // =============================================
        // CLIC DERECHO
        // =============================================
        if (clicDerecho &&
            !clicDerechoAnterior)
        {
            if (grid.esValida(fila, columna))
            {
                Node& nodo =
                    grid.getNodo(
                        fila,
                        columna
                    );

                // El destino no puede ser obstáculo
                if (!nodo.esObstaculo())
                {
                    destino = &nodo;

                    // Borrar camino anterior
                    camino.clear();
                }
            }
        }

        // =============================================
        // GUARDAR ESTADO ANTERIOR DEL MOUSE
        // =============================================
        clicIzquierdoAnterior =
            clicIzquierdo;

        clicDerechoAnterior =
            clicDerecho;

        // =============================================
        // DIBUJAR
        // =============================================
        ventana.clear(
            sf::Color::Black
        );

        grid.dibujar(
            ventana,
            camino,
            inicio,
            destino
        );

        ventana.display();
    }

    return 0;
}