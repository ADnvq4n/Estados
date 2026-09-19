#include "../include/Guilmon.hpp"

#include <cmath>

// ======================================================
// CONSTRUCTOR
// ======================================================

Guilmon::Guilmon()
{
    estadoActual = "Idle";

    // Grid:
    //
    // offsetX = 380
    // offsetY = 140
    // celda = 40
    //
    // Centro de la celda (0,0):
    //
    // X = 380 + 20 = 400
    // Y = 140 + 20 = 160

    posicion = sf::Vector2f(
        400.0f,
        160.0f
    );

    muerto = false;

    indiceCamino = 0;

    velocidadMovimiento = 120.0f;

    offsetX = 380.0f;

    offsetY = 140.0f;

    tamanoCelda = 40.0f;
}

// ======================================================
// CARGAR SPRITES
// ======================================================

bool Guilmon::cargarSprites()
{
    bool correcto = true;

    if (!idle.cargar("assets/sprites/idle"))
        correcto = false;

    if (!eating.cargar("assets/sprites/eating"))
        correcto = false;

    if (!win.cargar("assets/sprites/win"))
        correcto = false;

    if (!shocked.cargar("assets/sprites/shocked"))
        correcto = false;

    if (!lose.cargar("assets/sprites/lose"))
        correcto = false;

    // ==================================================
    // CENTRAR ORIGEN DE LOS SPRITES
    // ==================================================

    sf::FloatRect limites;

    limites = idle.getSprite().getLocalBounds();

    idle.getSprite().setOrigin(
        limites.left + limites.width / 2.0f,
        limites.top + limites.height / 2.0f
    );

    limites = eating.getSprite().getLocalBounds();

    eating.getSprite().setOrigin(
        limites.left + limites.width / 2.0f,
        limites.top + limites.height / 2.0f
    );

    limites = win.getSprite().getLocalBounds();

    win.getSprite().setOrigin(
        limites.left + limites.width / 2.0f,
        limites.top + limites.height / 2.0f
    );

    limites = shocked.getSprite().getLocalBounds();

    shocked.getSprite().setOrigin(
        limites.left + limites.width / 2.0f,
        limites.top + limites.height / 2.0f
    );

    limites = lose.getSprite().getLocalBounds();

    lose.getSprite().setOrigin(
        limites.left + limites.width / 2.0f,
        limites.top + limites.height / 2.0f
    );

    // ==================================================
    // POSICION INICIAL
    // ==================================================

    idle.getSprite().setPosition(posicion);

    eating.getSprite().setPosition(posicion);

    win.getSprite().setPosition(posicion);

    shocked.getSprite().setPosition(posicion);

    lose.getSprite().setPosition(posicion);

    return correcto;
}

// ======================================================
// CAMBIAR ESTADO
// ======================================================

void Guilmon::cambiarEstado(
    const std::string& nuevoEstado
)
{
    if (muerto)
        return;

    estadoActual = nuevoEstado;

    if (estadoActual == "Idle")
    {
        idle.reiniciar();
    }
    else if (estadoActual == "Eating")
    {
        eating.reiniciar();
    }
    else if (estadoActual == "Win")
    {
        win.reiniciar();
    }
    else if (estadoActual == "Shocked")
    {
        shocked.reiniciar();
    }
    else if (estadoActual == "Lose")
    {
        lose.reiniciar();
    }
}

// ======================================================
// ESTABLECER CAMINO
// ======================================================

void Guilmon::establecerCamino(
    const std::vector<Node*>& nuevoCamino,
    float nuevoOffsetX,
    float nuevoOffsetY,
    float nuevoTamanoCelda
)
{
    camino = nuevoCamino;

    offsetX = nuevoOffsetX;

    offsetY = nuevoOffsetY;

    tamanoCelda = nuevoTamanoCelda;

    // El nodo 0 es la posición actual.
    //
    // Por eso comenzamos con el nodo 1.

    if (camino.size() > 1)
    {
        indiceCamino = 1;
    }
    else
    {
        indiceCamino = 0;
    }
}

// ======================================================
// ESTABLECER POSICION
// ======================================================

void Guilmon::establecerPosicion(
    const sf::Vector2f& nuevaPosicion
)
{
    posicion = nuevaPosicion;

    // El camino anterior deja de ser válido.

    camino.clear();

    indiceCamino = 0;

    // Actualizar sprites.

    idle.getSprite().setPosition(posicion);

    eating.getSprite().setPosition(posicion);

    win.getSprite().setPosition(posicion);

    shocked.getSprite().setPosition(posicion);

    lose.getSprite().setPosition(posicion);
}

// ======================================================
// ACTUALIZAR
// ======================================================

void Guilmon::actualizar(
    float deltaTime
)
{
    if (muerto)
    {
        shocked.actualizar(deltaTime);

        return;
    }

    necesidades.actualizar(deltaTime);

    // ==================================================
    // MUERTE
    // ==================================================

    if (necesidades.estaMuerto())
    {
        muerto = true;

        estadoActual = "Shocked";

        shocked.reiniciar();

        return;
    }

    // ==================================================
    // BERRINCHE
    // ==================================================

    if (necesidades.estaEnBerrinche())
    {
        if (estadoActual != "Lose")
        {
            estadoActual = "Lose";

            lose.reiniciar();
        }
    }

    // ==================================================
    // MOVIMIENTO POR EL CAMINO A*
    // ==================================================

    if (
        !camino.empty() &&
        indiceCamino >= 0 &&
        indiceCamino <
        static_cast<int>(camino.size())
    )
    {
        Node* nodoObjetivo =
            camino[indiceCamino];

        // ==================================================
        // CENTRO EXACTO DE LA CELDA
        // ==================================================

        float objetivoX =
            offsetX +
            nodoObjetivo->getColumna()
            * tamanoCelda +
            tamanoCelda / 2.0f;

        float objetivoY =
            offsetY +
            nodoObjetivo->getFila()
            * tamanoCelda +
            tamanoCelda / 2.0f;

        // ==================================================
        // DISTANCIA AL CENTRO
        // ==================================================

        float dx =
            objetivoX - posicion.x;

        float dy =
            objetivoY - posicion.y;

        float distancia =
            std::sqrt(
                dx * dx +
                dy * dy
            );

        // ==================================================
        // YA LLEGAMOS A LA CELDA
        // ==================================================

        if (distancia <= 0.5f)
        {
            posicion.x = objetivoX;

            posicion.y = objetivoY;

            indiceCamino++;
        }

        // ==================================================
        // AVANZAR HACIA LA CELDA
        // ==================================================

        else
        {
            float direccionX =
                dx / distancia;

            float direccionY =
                dy / distancia;

            float movimiento =
                velocidadMovimiento *
                deltaTime;

            // Nunca avanzar más allá
            // del centro de la celda.

            if (movimiento >= distancia)
            {
                posicion.x = objetivoX;

                posicion.y = objetivoY;

                indiceCamino++;
            }
            else
            {
                posicion.x +=
                    direccionX *
                    movimiento;

                posicion.y +=
                    direccionY *
                    movimiento;
            }
        }

        // ==================================================
        // ACTUALIZAR TODOS LOS SPRITES
        // ==================================================

        idle.getSprite().setPosition(
            posicion
        );

        eating.getSprite().setPosition(
            posicion
        );

        win.getSprite().setPosition(
            posicion
        );

        shocked.getSprite().setPosition(
            posicion
        );

        lose.getSprite().setPosition(
            posicion
        );
    }

    // ==================================================
    // ANIMACION
    // ==================================================

    if (estadoActual == "Idle")
    {
        idle.actualizar(deltaTime);
    }
    else if (estadoActual == "Eating")
    {
        eating.actualizar(deltaTime);
    }
    else if (estadoActual == "Win")
    {
        win.actualizar(deltaTime);
    }
    else if (estadoActual == "Shocked")
    {
        shocked.actualizar(deltaTime);
    }
    else if (estadoActual == "Lose")
    {
        lose.actualizar(deltaTime);
    }
}

// ======================================================
// DIBUJAR
// ======================================================

void Guilmon::dibujar(
    sf::RenderWindow& ventana
)
{
    if (estadoActual == "Idle")
    {
        idle.dibujar(ventana);
    }
    else if (estadoActual == "Eating")
    {
        eating.dibujar(ventana);
    }
    else if (estadoActual == "Win")
    {
        win.dibujar(ventana);
    }
    else if (estadoActual == "Shocked")
    {
        shocked.dibujar(ventana);
    }
    else if (estadoActual == "Lose")
    {
        lose.dibujar(ventana);
    }
}

// ======================================================
// ALIMENTAR
// ======================================================

void Guilmon::alimentar()
{
    if (!muerto)
    {
        necesidades.alimentar();

        cambiarEstado("Eating");
    }
}

// ======================================================
// DORMIR
// ======================================================

void Guilmon::dormir()
{
    if (!muerto)
    {
        necesidades.dormir();

        cambiarEstado("Win");
    }
}

// ======================================================
// CURAR
// ======================================================

void Guilmon::curar()
{
    if (!muerto)
    {
        necesidades.curar();

        cambiarEstado("Idle");
    }
}

// ======================================================
// GETTERS
// ======================================================

float Guilmon::getVida() const
{
    return necesidades.getVida();
}

float Guilmon::getComida() const
{
    return necesidades.getComida();
}

float Guilmon::getSueno() const
{
    return necesidades.getSueno();
}

std::string Guilmon::getEstado() const
{
    return estadoActual;
}

bool Guilmon::estaMuerto() const
{
    return muerto;
}

sf::Vector2f Guilmon::getPosicion() const
{
    return posicion;
}