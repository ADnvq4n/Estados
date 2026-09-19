# Diagrama de estados (PlantUML)
plantuml
@startuml

[*] --> Idle

state Idle {
    Idle : Guilmon tranquilo
}

state Eating {
    Eating : Guilmon comiendo
}

state Win {
    Win : Guilmon durmiendo
}

state Lose {
    Lose : Guilmon haciendo berrinche
}

state Shocked {
    Shocked : Guilmon muerto
}

Idle --> Eating : Alimentar
Eating --> Idle : Termina de comer

Idle --> Win : Dormir
Win --> Idle : Despertar

Idle --> Lose : Necesidades bajas
Lose --> Idle : Se recupera

Idle --> Shocked : Vida <= 0
Eating --> Shocked : Vida <= 0
Win --> Shocked : Vida <= 0
Lose --> Shocked : Vida <= 0

Shocked --> [*]

@enduml

