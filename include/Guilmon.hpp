#ifndef GUILMON_HPP
#define GUILMON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Idle.hpp"
#include "Eating.hpp"
#include "Win.hpp"
#include "Shocked.hpp"
#include "Lose.hpp"
#include "Necesidades.hpp"
#include "Node.hpp"

class Guilmon
{
private:

    Idle idle;
    Eating eating;
    Win win;
    Shocked shocked;
    Lose lose;

    Necesidades necesidades;

    std::string estadoActual;

    sf::Vector2f posicion;

    bool muerto;

    // Camino calculado por A*
    std::vector<Node*> camino;

    // Nodo que Guilmon está siguiendo
    int indiceCamino;

    // Velocidad de movimiento
    float velocidadMovimiento;

    // Datos del Grid
    float offsetX;
    float offsetY;
    float tamanoCelda;

public:

    Guilmon();

    bool cargarSprites();

    void cambiarEstado(
        const std::string& nuevoEstado
    );

    void actualizar(
        float deltaTime
    );

    void dibujar(
        sf::RenderWindow& ventana
    );

    void alimentar();

    void dormir();

    void curar();

    float getVida() const;

    float getComida() const;

    float getSueno() const;

    std::string getEstado() const;

    bool estaMuerto() const;

    // ==============================
    // CAMINO A*
    // ==============================

    void establecerCamino(
        const std::vector<Node*>& nuevoCamino,
        float nuevoOffsetX,
        float nuevoOffsetY,
        float nuevoTamanoCelda
    );

    // ==============================
    // POSICION
    // ==============================

    void establecerPosicion(
        const sf::Vector2f& nuevaPosicion
    );

    sf::Vector2f getPosicion() const;
};

#endif