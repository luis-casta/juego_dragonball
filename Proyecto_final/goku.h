#ifndef GOKU_H
#define GOKU_H

#include "objetojuego.h"

class Goku : public ObjetoJuego
{
public:
    Goku(float x, float y, QString archivoSprite);

    void actualizar(float tiempo) override;
    void dibujar(QPainter& pintor) override;
    void setColision(ObjetoJuego* otro) override;

    void moverIzquierda();
    void moverDerecha();
    void moverArriba();
    void moverAbajo();
};

#endif // GOKU_H
