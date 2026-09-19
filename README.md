# Guilmon Tamagotchi

## Descripción

Este proyecto consiste en una mascota virtual tipo **Tamagotchi**, desarrollada en C++ utilizando la biblioteca gráfica **SFML**.

El proyecto aplica los principios de **Programación Orientada a Objetos (POO)** para controlar los diferentes estados y necesidades de Guilmon.

Además, se implementó el algoritmo de búsqueda **A*** para permitir que Guilmon encuentre y siga un camino dentro de un tablero evitando obstáculos.

## Tecnologías utilizadas

* C++
* SFML
* MinGW / MSYS2
* Programación Orientada a Objetos
* Algoritmo de búsqueda A*
* Git y GitHub

## Características

El programa cuenta con las siguientes funciones:

* Animaciones de Guilmon mediante sprites.
* Sistema de estados.
* Sistema de necesidades.
* Barra de vida.
* Barra de comida.
* Barra de sueño.
* Alimentar a Guilmon.
* Dormir a Guilmon.
* Curar a Guilmon.
* Sistema de muerte.
* Estado de berrinche.
* Tablero de movimiento de 10 × 10.
* Selección de posición inicial.
* Selección de destino.
* Colocación y eliminación de obstáculos.
* Cálculo automático de rutas mediante A*.
* Movimiento de Guilmon siguiendo el camino calculado.
* Guilmon evita las celdas que contienen obstáculos.

# Estados de Guilmon

El programa cuenta con cinco estados principales:

| Estado  | Descripción                          |
| ------- | ------------------------------------ |
| Idle    | Guilmon permanece tranquilo          |
| Eating  | Guilmon está comiendo                |
| Win     | Guilmon está durmiendo               |
| Shocked | Guilmon representa la muerte         |
| Lose    | Guilmon entra en estado de berrinche |

Los estados se controlan mediante programación orientada a objetos y cada uno cuenta con su propia clase.

# Necesidades

Guilmon cuenta con tres necesidades principales:

* Vida
* Comida
* Sueño

Estas necesidades disminuyen con el paso del tiempo.

El usuario puede modificar algunas de ellas mediante los botones de la interfaz.

### Alimentar

Aumenta la comida y recupera una pequeña cantidad de vida.

### Dormir

Aumenta el nivel de sueño.

### Curar

Recupera vida.

Si alguna de las necesidades llega a cero, Guilmon muere.

Cuando las necesidades se encuentran en niveles bajos, Guilmon puede entrar en estado de berrinche.

# Sistema de movimiento

El programa cuenta con un tablero de **10 × 10 celdas**.

Cada celda tiene un tamaño de:

40 × 40 píxeles

El tablero se encuentra en la parte derecha de la ventana.

Cada celda puede encontrarse en alguno de los siguientes estados:

* Libre
* Obstáculo
* Inicio
* Destino
* Camino


# Algoritmo A*

Para encontrar el camino de Guilmon se utiliza el algoritmo de búsqueda **A***.

A* permite encontrar una ruta entre una posición inicial y una posición de destino evitando las celdas que contienen obstáculos.

El algoritmo utiliza tres valores principales:

g = costo del camino recorrido
h = estimación de distancia hasta el destino
f = costo total

El costo total se calcula mediante:

f = g + h

Para este proyecto se utiliza como heurística la distancia Manhattan:

h = |filaActual - filaDestino|
  + |columnaActual - columnaDestino|


El movimiento de Guilmon utiliza cuatro direcciones:

        ↑
        |
    ←   +   →
        |
        ↓

Por lo tanto, Guilmon no se mueve diagonalmente.


# Selección del camino

El usuario puede seleccionar el recorrido mediante el mouse.

## 1. Seleccionar inicio

Con el **clic izquierdo** sobre una celda libre se establece la posición inicial de Guilmon.

La celda se representa de color verde.

🟢 = Inicio

Guilmon se coloca en el centro de esa celda.

## 2. Seleccionar destino

Después de seleccionar el inicio, se utiliza nuevamente el **clic izquierdo** sobre otra celda libre para establecer el destino.

La celda se representa de color rojo.

🔴 = Destino

Después de seleccionar el destino, el algoritmo A* calcula automáticamente el camino.

# Obstáculos

Los obstáculos se pueden colocar utilizando el **clic derecho** sobre una celda.

Una celda con obstáculo se representa visualmente con una textura.

🧱 = Obstáculo

A* no puede utilizar una celda que contenga un obstáculo.

Los obstáculos también pueden eliminarse utilizando nuevamente el clic derecho sobre la misma celda.

No es posible colocar un obstáculo sobre:

* El inicio.
* El destino.

# Camino encontrado

Cuando A* encuentra una ruta, las celdas que forman el camino se muestran de color azul.

Por ejemplo:

🟢 🔵 🔵 🔵 🔵 🔴

Guilmon recorre el camino desde el inicio hasta el destino.

Cuando existen obstáculos, A* busca una ruta alternativa.

        🧱
        🧱
🟢 🔵 🔵 🧱
        🔵
        🔵
        🔵 🔴

Guilmon rodea el obstáculo en lugar de atravesarlo.


# Movimiento de Guilmon

Guilmon no se mueve directamente hacia el destino.

Primero A* genera una lista de nodos:

Inicio
  ↓
Nodo 1
  ↓
Nodo 2
  ↓
Nodo 3
  ↓
Destino

Guilmon sigue cada nodo de manera consecutiva.

Además, el sprite de Guilmon se coloca en el **centro de cada celda** para que visualmente siga el camino correctamente.

# Cuando no existe un camino

Si el destino está completamente bloqueado, A* no devuelve una ruta.

🧱 🧱 🧱
🧱 🔴 🧱
🧱 🧱 🧱

y Guilmon no comienza el movimiento.

# Controles

## Mouse

| Acción            | Función                       |
| ----------------- | ----------------------------- |
| Clic izquierdo    | Seleccionar inicio/destino    |
| Clic derecho      | Colocar o eliminar obstáculos |
| Clic en Alimentar | Aumentar comida               |
| Clic en Dormir    | Aumentar sueño                |
| Clic en Curar     | Recuperar vida                |

## Teclado

| Tecla | Estado  |
| ----- | ------- |
| I     | Idle    |
| E     | Eating  |
| W     | Win     |
| S     | Shocked |
| L     | Lose    |

Objetivo del proyecto

El objetivo es desarrollar una mascota virtual utilizando **Programación Orientada a Objetos, integrando animaciones, estados, necesidades y un sistema de navegación mediante el algoritmo A*.

De esta manera, Guilmon puede interactuar con el usuario y desplazarse dentro de un entorno con obstáculos utilizando una ruta calculada automáticamente.

Creador: Alex Daniel Velazquez Andrade Grupo: 6E Registro: 24110229