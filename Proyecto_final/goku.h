#ifndef GOKU_H
#define GOKU_H

#include "objetojuego.h"

enum DireccionMovimiento {
    QUIETO = 0,
    DERECHA,
    IZQUIERDA,
    ARRIBA,
    ABAJO
};

class Goku : public ObjetoJuego
{
public:
    Goku(float x, float y, QString archivoSprite);

    void actualizar(float tiempo) override;
    void dibujar(QPainter& pintor) override;

    void moverIzquierda();
    void moverDerecha();
    void detenerMovimiento();

    void cambiarDireccion(DireccionMovimiento nuevaDireccion);

private:
    int cuadroActual;
    int anchoCuadro;
    int altoCuadro;
    int cuadrosPorFila;
    int velocidadAnimacion;
    int contadorAnimacion;
    DireccionMovimiento direccionActual;

    void actualizarCuadro();
    int obtenerIndiceCuadro(DireccionMovimiento direccion, int frame);
};

#endif // GOKU_H
