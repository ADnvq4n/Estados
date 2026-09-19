#include "../include/Necesidades.hpp"

Necesidades::Necesidades()
{
    vida = 100.0f;
    comida = 100.0f;
    sueno = 100.0f;

    velocidadDisminucion = 2.0f;
}

void Necesidades::actualizar(float deltaTime)
{
    vida -= velocidadDisminucion * deltaTime;
    comida -= velocidadDisminucion * deltaTime;
    sueno -= velocidadDisminucion * deltaTime;

    if (vida < 0.0f)
    {
        vida = 0.0f;
    }

    if (comida < 0.0f)
    {
        comida = 0.0f;
    }

    if (sueno < 0.0f)
    {
        sueno = 0.0f;
    }
}

void Necesidades::alimentar()
{
    comida += 25.0f;

    if (comida > 100.0f)
    {
        comida = 100.0f;
    }

    vida += 5.0f;

    if (vida > 100.0f)
    {
        vida = 100.0f;
    }
}

void Necesidades::dormir()
{
    sueno += 30.0f;

    if (sueno > 100.0f)
    {
        sueno = 100.0f;
    }
}

void Necesidades::curar()
{
    vida += 25.0f;

    if (vida > 100.0f)
    {
        vida = 100.0f;
    }
}

float Necesidades::getVida() const
{
    return vida;
}

float Necesidades::getComida() const
{
    return comida;
}

float Necesidades::getSueno() const
{
    return sueno;
}

bool Necesidades::estaEnBerrinche() const
{
    return vida <= 50.0f &&
           comida <= 50.0f &&
           sueno <= 50.0f;
}

bool Necesidades::estaMuerto() const
{
    return vida <= 0.0f ||
           comida <= 0.0f ||
           sueno <= 0.0f;
}
