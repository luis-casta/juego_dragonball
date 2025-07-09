#ifndef GOKU_H
#define GOKU_H

#include "objetojuego.h"

enum DireccionMovimiento {
    QUIETO = 0,
    DERECHA = 1,
    IZQUIERDA = 2,
    ARRIBA = 3,
    ABAJO = 4
};

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
    void detenerMovimiento();

    void establecerLimites(int ancho, int alto);

private:
    int cuadroActual;
    int cuadrosPorFila;
    int anchoCuadro;
    int altoCuadro;
    int contadorAnimacion;
    int velocidadAnimacion;
    DireccionMovimiento direccionActual;
    DireccionMovimiento ultimaDireccion;

    int limiteAncho;
    int limiteAlto;


    bool moviendose;
    int tiempoQuieto;
    float velocidadMovimiento;

    void cambiarDireccion(DireccionMovimiento nuevaDireccion);
    int obtenerCuadroParaDireccion(DireccionMovimiento direccion, int frame);
    int obtenerCuadrosParaDireccion(DireccionMovimiento direccion);
};

#endif // GOKU_H
