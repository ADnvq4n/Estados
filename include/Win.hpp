#ifndef WIN_HPP
#define WIN_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Win
{
private:
    std::vector<sf::Texture> texturas;
    sf::Sprite sprite;

    int frameActual;
    float tiempoFrame;
    float velocidadFrame;

public:
    Win();

    bool cargar(const std::string& carpeta);
    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& ventana);
    void reiniciar();

    sf::Sprite& getSprite();
};

#endif
