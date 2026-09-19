#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "../include/Guilmon.hpp"
#include "../include/AStar.hpp"
#include "../include/Grid.hpp"

// ======================================================
// DIBUJAR BARRA
// ======================================================

void dibujarBarra(
    sf::RenderWindow& ventana,
    float valor,
    float x,
    float y,
    const sf::Color& color
)
{
    const float ancho = 250.0f;
    const float alto = 20.0f;

    sf::RectangleShape fondo;

    fondo.setSize(
        sf::Vector2f(
            ancho,
            alto
        )
    );

    fondo.setPosition(
        x,
        y
    );

    fondo.setFillColor(
        sf::Color(60, 60, 60)
    );

    sf::RectangleShape barra;

    barra.setSize(
        sf::Vector2f(
            ancho * (valor / 100.0f),
            alto
        )
    );

    barra.setPosition(
        x,
        y
    );

    barra.setFillColor(
        color
    );

    ventana.draw(fondo);

    ventana.draw(barra);
}

// ======================================================
// MAIN
// ======================================================

int main()
{
    // ==================================================
    // VENTANA
    // ==================================================

    sf::RenderWindow ventana(
        sf::VideoMode(800, 600),
        "Guilmon Tamagotchi"
    );

    ventana.setFramerateLimit(60);

    // ==================================================
    // GUILMON
    // ==================================================

    Guilmon guilmon;

    if (!guilmon.cargarSprites())
    {
        std::cout
            << "Error al cargar los sprites."
            << std::endl;

        return 1;
    }

    // ==================================================
    // FUENTE
    // ==================================================

    sf::Font fuente;

    if (!fuente.loadFromFile(
            "assets/arial.ttf"))
    {
        std::cout
            << "Error al cargar la fuente."
            << std::endl;

        return 1;
    }

    // ==================================================
    // GRID
    // ==================================================

    Grid grid(
        10,
        10,
        40.0f,
        380.0f,
        140.0f
    );

    // ==================================================
    // A*
    // ==================================================

    AStar buscador;

    std::vector<Node*> camino;

    Node* inicio = nullptr;

    Node* destino = nullptr;

    // ==================================================
    // MODO
    // ==================================================

    bool seleccionandoInicio = true;

    // ==================================================
    // BOTON ALIMENTAR
    // ==================================================

    sf::RectangleShape botonAlimentar;

    botonAlimentar.setSize(
        sf::Vector2f(
            150.0f,
            50.0f
        )
    );

    botonAlimentar.setPosition(
        30.0f,
        150.0f
    );

    botonAlimentar.setFillColor(
        sf::Color(80, 170, 80)
    );

    // ==================================================
    // BOTON DORMIR
    // ==================================================

    sf::RectangleShape botonDormir;

    botonDormir.setSize(
        sf::Vector2f(
            150.0f,
            50.0f
        )
    );

    botonDormir.setPosition(
        200.0f,
        150.0f
    );

    botonDormir.setFillColor(
        sf::Color(80, 100, 190)
    );

    // ==================================================
    // BOTON CURAR
    // ==================================================

    sf::RectangleShape botonCurar;

    botonCurar.setSize(
        sf::Vector2f(
            150.0f,
            50.0f
        )
    );

    botonCurar.setPosition(
        30.0f,
        220.0f
    );

    botonCurar.setFillColor(
        sf::Color(190, 80, 80)
    );

    // ==================================================
    // TEXTOS
    // ==================================================

    sf::Text textoAlimentar(
        "ALIMENTAR",
        fuente,
        20
    );

    textoAlimentar.setFillColor(
        sf::Color::White
    );

    textoAlimentar.setPosition(
        48.0f,
        163.0f
    );

    sf::Text textoDormir(
        "DORMIR",
        fuente,
        20
    );

    textoDormir.setFillColor(
        sf::Color::White
    );

    textoDormir.setPosition(
        242.0f,
        163.0f
    );

    sf::Text textoCurar(
        "CURAR",
        fuente,
        20
    );

    textoCurar.setFillColor(
        sf::Color::White
    );

    textoCurar.setPosition(
        68.0f,
        233.0f
    );

    // ==================================================
    // ESTADO
    // ==================================================

    sf::Text textoEstado(
        "Estado: Idle",
        fuente,
        22
    );

    textoEstado.setFillColor(
        sf::Color::White
    );

    textoEstado.setPosition(
        30.0f,
        300.0f
    );

    // ==================================================
    // MODO A*
    // ==================================================

    sf::Text textoModo(
        "Selecciona el INICIO",
        fuente,
        18
    );

    textoModo.setFillColor(
        sf::Color::White
    );

    textoModo.setPosition(
        380.0f,
        110.0f
    );

    // ==================================================
    // RELOJ
    // ==================================================

    sf::Clock reloj;

    // ==================================================
    // BUCLE
    // ==================================================

    while (ventana.isOpen())
    {
        sf::Event evento;

        while (ventana.pollEvent(evento))
        {
            // ==================================================
            // CERRAR
            // ==================================================

            if (
                evento.type ==
                sf::Event::Closed
            )
            {
                ventana.close();
            }

            // ==================================================
            // TECLADO
            // ==================================================

            if (
                evento.type ==
                sf::Event::KeyPressed
            )
            {
                if (
                    evento.key.code ==
                    sf::Keyboard::I
                )
                {
                    guilmon.cambiarEstado(
                        "Idle"
                    );
                }

                if (
                    evento.key.code ==
                    sf::Keyboard::E
                )
                {
                    guilmon.cambiarEstado(
                        "Eating"
                    );
                }

                if (
                    evento.key.code ==
                    sf::Keyboard::W
                )
                {
                    guilmon.cambiarEstado(
                        "Win"
                    );
                }

                if (
                    evento.key.code ==
                    sf::Keyboard::S
                )
                {
                    guilmon.cambiarEstado(
                        "Shocked"
                    );
                }

                if (
                    evento.key.code ==
                    sf::Keyboard::L
                )
                {
                    guilmon.cambiarEstado(
                        "Lose"
                    );
                }
            }

            // ==================================================
            // MOUSE
            // ==================================================

            if (
                evento.type ==
                sf::Event::MouseButtonPressed
            )
            {
                sf::Vector2f posicionMouse(
                    static_cast<float>(
                        evento.mouseButton.x
                    ),
                    static_cast<float>(
                        evento.mouseButton.y
                    )
                );

                // ==================================================
                // BOTONES
                // ==================================================

                if (
                    evento.mouseButton.button ==
                    sf::Mouse::Left
                )
                {
                    if (
                        botonAlimentar
                            .getGlobalBounds()
                            .contains(
                                posicionMouse
                            )
                    )
                    {
                        guilmon.alimentar();

                        continue;
                    }

                    if (
                        botonDormir
                            .getGlobalBounds()
                            .contains(
                                posicionMouse
                            )
                    )
                    {
                        guilmon.dormir();

                        continue;
                    }

                    if (
                        botonCurar
                            .getGlobalBounds()
                            .contains(
                                posicionMouse
                            )
                    )
                    {
                        guilmon.curar();

                        continue;
                    }
                }

                // ==================================================
                // DATOS GRID
                // ==================================================

                float offsetX =
                    grid.getOffsetX();

                float offsetY =
                    grid.getOffsetY();

                float tamanoCelda =
                    grid.getTamanoCelda();

                float mapaAncho =
                    grid.getColumnas()
                    * tamanoCelda;

                float mapaAlto =
                    grid.getFilas()
                    * tamanoCelda;

                // ==================================================
                // CLICK DENTRO DEL MAPA
                // ==================================================

                bool dentroDelMapa =
                    posicionMouse.x >= offsetX &&
                    posicionMouse.x <
                        offsetX + mapaAncho &&
                    posicionMouse.y >= offsetY &&
                    posicionMouse.y <
                        offsetY + mapaAlto;

                if (!dentroDelMapa)
                {
                    continue;
                }

                // ==================================================
                // CALCULAR FILA Y COLUMNA
                // ==================================================

                int columna =
                    static_cast<int>(
                        (
                            posicionMouse.x -
                            offsetX
                        ) /
                        tamanoCelda
                    );

                int fila =
                    static_cast<int>(
                        (
                            posicionMouse.y -
                            offsetY
                        ) /
                        tamanoCelda
                    );

                if (
                    !grid.esValida(
                        fila,
                        columna
                    )
                )
                {
                    continue;
                }

                Node* nodo =
                    &grid.getNodo(
                        fila,
                        columna
                    );

                // ==================================================
                // CLIC DERECHO
                // OBSTACULO
                // ==================================================

                if (
                    evento.mouseButton.button ==
                    sf::Mouse::Right
                )
                {
                    if (nodo == inicio)
                    {
                        std::cout
                            << "No puedes poner "
                            << "un obstaculo en "
                            << "el inicio."
                            << std::endl;

                        continue;
                    }

                    if (nodo == destino)
                    {
                        std::cout
                            << "No puedes poner "
                            << "un obstaculo en "
                            << "el destino."
                            << std::endl;

                        continue;
                    }

                    grid.alternarObstaculo(
                        fila,
                        columna
                    );

                    // El camino anterior ya no
                    // necesariamente es valido.

                    camino.clear();

                    std::cout
                        << "Obstaculo "
                        << (
                            nodo->esObstaculo()
                                ? "colocado"
                                : "quitado"
                        )
                        << " en ("
                        << fila
                        << ", "
                        << columna
                        << ")"
                        << std::endl;

                    continue;
                }

                // ==================================================
                // CLIC IZQUIERDO
                // ==================================================

                if (
                    evento.mouseButton.button ==
                    sf::Mouse::Left
                )
                {
                    // No seleccionar obstáculos.

                    if (nodo->esObstaculo())
                    {
                        std::cout
                            << "No puedes seleccionar "
                            << "un obstaculo."
                            << std::endl;

                        continue;
                    }

                    // ==================================================
                    // SELECCIONAR INICIO
                    // ==================================================

                    if (seleccionandoInicio)
                    {
                        inicio = nodo;

                        destino = nullptr;

                        camino.clear();

                        // Centro de la celda.

                        float nuevaX =
                            offsetX +
                            columna *
                                tamanoCelda +
                            tamanoCelda / 2.0f;

                        float nuevaY =
                            offsetY +
                            fila *
                                tamanoCelda +
                            tamanoCelda / 2.0f;

                        // Colocar Guilmon
                        // EXACTAMENTE en el centro.

                        guilmon.establecerPosicion(
                            sf::Vector2f(
                                nuevaX,
                                nuevaY
                            )
                        );

                        seleccionandoInicio = false;

                        textoModo.setString(
                            "Selecciona el DESTINO"
                        );

                        std::cout
                            << "Inicio: ("
                            << fila
                            << ", "
                            << columna
                            << ")"
                            << std::endl;

                        continue;
                    }

                    // ==================================================
                    // SELECCIONAR DESTINO
                    // ==================================================

                    if (nodo == inicio)
                    {
                        std::cout
                            << "El destino debe ser "
                            << "diferente al inicio."
                            << std::endl;

                        continue;
                    }

                    destino = nodo;

                    // ==================================================
                    // CALCULAR A*
                    // ==================================================

                    camino =
                        buscador.encontrarCamino(
                            grid,
                            inicio,
                            destino
                        );

                    // ==================================================
                    // NO HAY CAMINO
                    // ==================================================

                    if (camino.empty())
                    {
                        std::cout
                            << "No existe un camino "
                            << "entre el inicio y "
                            << "el destino."
                            << std::endl;

                        textoModo.setString(
                            "No existe camino"
                        );
                    }

                    // ==================================================
                    // CAMINO ENCONTRADO
                    // ==================================================

                    else
                    {
                        guilmon.establecerCamino(
                            camino,
                            offsetX,
                            offsetY,
                            tamanoCelda
                        );

                        textoModo.setString(
                            "Camino encontrado"
                        );

                        std::cout
                            << "Camino encontrado: "
                            << camino.size()
                            << " nodos."
                            << std::endl;
                    }

                    // El siguiente clic izquierdo
                    // vuelve a seleccionar inicio.

                    seleccionandoInicio = true;
                }
            }
        }

        // ==================================================
        // DELTA TIME
        // ==================================================

        float deltaTime =
            reloj.restart().asSeconds();

        // ==================================================
        // ACTUALIZAR GUILMON
        // ==================================================

        guilmon.actualizar(
            deltaTime
        );

        // ==================================================
        // ACTUALIZAR ESTADO
        // ==================================================

        textoEstado.setString(
            "Estado: " +
            guilmon.getEstado()
        );

        // ==================================================
        // LIMPIAR
        // ==================================================

        ventana.clear(
            sf::Color(25, 25, 30)
        );

        // ==================================================
        // BARRAS
        // ==================================================

        dibujarBarra(
            ventana,
            guilmon.getVida(),
            30.0f,
            30.0f,
            sf::Color(220, 70, 70)
        );

        dibujarBarra(
            ventana,
            guilmon.getComida(),
            30.0f,
            65.0f,
            sf::Color(230, 160, 50)
        );

        dibujarBarra(
            ventana,
            guilmon.getSueno(),
            30.0f,
            100.0f,
            sf::Color(90, 130, 230)
        );

        // ==================================================
        // BOTONES
        // ==================================================

        ventana.draw(
            botonAlimentar
        );

        ventana.draw(
            botonDormir
        );

        ventana.draw(
            botonCurar
        );

        // ==================================================
        // TEXTOS
        // ==================================================

        ventana.draw(
            textoAlimentar
        );

        ventana.draw(
            textoDormir
        );

        ventana.draw(
            textoCurar
        );

        ventana.draw(
            textoEstado
        );

        ventana.draw(
            textoModo
        );

        // ==================================================
        // GRID
        // ==================================================

        grid.dibujar(
            ventana,
            camino,
            inicio,
            destino
        );

        // ==================================================
        // GUILMON
        // ==================================================

        guilmon.dibujar(
            ventana
        );

        // ==================================================
        // MOSTRAR
        // ==================================================

        ventana.display();
    }

    return 0;
}