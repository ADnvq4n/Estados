#ifndef IDLE_HPP
#define IDLE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Idle
{
private:
    std::vector<sf::Texture> texturas;
    sf::Sprite sprite;

    int frameActual;
    float tiempoFrame;
    float velocidadFrame;

public:
    Idle();

    bool cargar(const std::string& carpeta);
    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& ventana);
    void reiniciar();

    sf::Sprite& getSprite();
};

#endif
