#ifndef NECESIDADES_HPP
#define NECESIDADES_HPP

class Necesidades
{
private:
    float vida;
    float comida;
    float sueno;

    float velocidadDisminucion;

public:
    Necesidades();

    void actualizar(float deltaTime);

    void alimentar();
    void dormir();
    void curar();

    float getVida() const;
    float getComida() const;
    float getSueno() const;

    bool estaEnBerrinche() const;
    bool estaMuerto() const;
};

#endif
