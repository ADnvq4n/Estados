#include "../include/Win.hpp"

#include <filesystem>
#include <algorithm>
#include <utility>

namespace fs = std::filesystem;

Win::Win()
{
    frameActual = 0;
    tiempoFrame = 0.0f;
    velocidadFrame = 0.15f;
}

bool Win::cargar(const std::string& carpeta)
{
    std::vector<std::string> archivos;

    if (!fs::exists(carpeta))
    {
        return false;
    }

    for (const auto& archivo : fs::directory_iterator(carpeta))
    {
        if (archivo.path().extension() == ".png")
        {
            archivos.push_back(archivo.path().string());
        }
    }

    std::sort(archivos.begin(), archivos.end());

    if (archivos.empty())
    {
        return false;
    }

    for (const std::string& archivo : archivos)
    {
        sf::Texture textura;

        if (!textura.loadFromFile(archivo))
        {
            return false;
        }

        texturas.push_back(std::move(textura));
    }

    sprite.setTexture(texturas[0]);

    return true;
}

void Win::actualizar(float deltaTime)
{
    if (texturas.empty())
    {
        return;
    }

    tiempoFrame += deltaTime;

    if (tiempoFrame >= velocidadFrame)
    {
        tiempoFrame = 0.0f;

        frameActual++;

        if (frameActual >= static_cast<int>(texturas.size()))
        {
            frameActual = 0;
        }

        sprite.setTexture(texturas[frameActual]);
    }
}

void Win::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(sprite);
}

void Win::reiniciar()
{
    frameActual = 0;
    tiempoFrame = 0.0f;

    if (!texturas.empty())
    {
        sprite.setTexture(texturas[0]);
    }
}

sf::Sprite& Win::getSprite()
{
    return sprite;
}

