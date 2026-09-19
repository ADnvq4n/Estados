#include "../include/Node.hpp"

// Constructor por defecto
Node::Node()
{
    fila = 0;
    columna = 0;

    obstaculo = false;

    g = 0.0f;
    h = 0.0f;
    f = 0.0f;

    padre = nullptr;
}

// Constructor con posición
Node::Node(int fila, int columna)
{
    this->fila = fila;
    this->columna = columna;

    obstaculo = false;

    g = 0.0f;
    h = 0.0f;
    f = 0.0f;

    padre = nullptr;
}

// Obtener fila
int Node::getFila() const
{
    return fila;
}

// Obtener columna
int Node::getColumna() const
{
    return columna;
}

// Saber si es obstáculo
bool Node::esObstaculo() const
{
    return obstaculo;
}

// Establecer obstáculo
void Node::setObstaculo(bool valor)
{
    obstaculo = valor;
}

// Obtener G
float Node::getG() const
{
    return g;
}

// Obtener H
float Node::getH() const
{
    return h;
}

// Obtener F
float Node::getF() const
{
    return f;
}

// Establecer G
void Node::setG(float valor)
{
    g = valor;
}

// Establecer H
void Node::setH(float valor)
{
    h = valor;
}

// Calcular F = G + H
void Node::calcularF()
{
    f = g + h;
}

// Obtener padre
Node* Node::getPadre() const
{
    return padre;
}

// Establecer padre
void Node::setPadre(Node* nodo)
{
    padre = nodo;
}
