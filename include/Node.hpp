#ifndef NODE_HPP
#define NODE_HPP

class Node
{
private:
    int fila;
    int columna;

    bool obstaculo;

    float g;
    float h;
    float f;

    Node* padre;

public:
    Node();

    Node(int fila, int columna);

    int getFila() const;
    int getColumna() const;

    bool esObstaculo() const;
    void setObstaculo(bool valor);

    float getG() const;
    float getH() const;
    float getF() const;

    void setG(float valor);
    void setH(float valor);
    void calcularF();

    Node* getPadre() const;
    void setPadre(Node* nodo);
};

#endif