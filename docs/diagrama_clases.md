# Diagrama de clases (PlantUML)
plantuml
@startuml

class Guilmon {

    - estadoActual: std::string
    - posicion: sf::Vector2f
    - vida: float
    - comida: float
    - sueno: float

    + Guilmon()
    + cargarSprites(): bool
    + cambiarEstado(nuevoEstado: std::string): void
    + actualizar(deltaTime: float): void
    + dibujar(ventana: sf::RenderWindow): void
    + getEstado(): std::string

    + alimentar(): void
    + dormir(): void
    + curar(): void

    + getVida(): float
    + getComida(): float
    + getSueno(): float
}


class Idle {

    - sprite: sf::Sprite
    - textura: sf::Texture
    - frames: std::vector<sf::Texture>

    + cargar(ruta: std::string): bool
    + actualizar(deltaTime: float): void
    + dibujar(ventana: sf::RenderWindow): void
    + reiniciar(): void
}


class Eating {

    - sprite: sf::Sprite
    - textura: sf::Texture
    - frames: std::vector<sf::Texture>

    + cargar(ruta: std::string): bool
    + actualizar(deltaTime: float): void
    + dibujar(ventana: sf::RenderWindow): void
    + reiniciar(): void
}


class Win {

    - sprite: sf::Sprite
    - textura: sf::Texture
    - frames: std::vector<sf::Texture>

    + cargar(ruta: std::string): bool
    + actualizar(deltaTime: float): void
    + dibujar(ventana: sf::RenderWindow): void
    + reiniciar(): void
}


class Shocked {

    - sprite: sf::Sprite
    - textura: sf::Texture
    - frames: std::vector<sf::Texture>

    + cargar(ruta: std::string): bool
    + actualizar(deltaTime: float): void
    + dibujar(ventana: sf::RenderWindow): void
    + reiniciar(): void
}


class Lose {

    - sprite: sf::Sprite
    - textura: sf::Texture
    - frames: std::vector<sf::Texture>

    + cargar(ruta: std::string): bool
    + actualizar(deltaTime: float): void
    + dibujar(ventana: sf::RenderWindow): void
    + reiniciar(): void
}


class Necesidades {

    - vida: float
    - comida: float
    - sueno: float
    - velocidadDisminucion: float

    + Necesidades()
    + actualizar(deltaTime: float): void
    + alimentar(): void
    + dormir(): void
    + curar(): void
    + getVida(): float
    + getComida(): float
    + getSueno(): float
    + estaEnBerrinche(): bool
    + estaMuerto(): bool
}


Guilmon *-- Idle
Guilmon *-- Eating
Guilmon *-- Win
Guilmon *-- Shocked
Guilmon *-- Lose

Guilmon *-- Necesidades

@enduml

