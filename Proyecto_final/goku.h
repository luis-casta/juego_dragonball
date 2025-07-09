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

enum EstadoSalto {
    SIN_SALTO,
    SUBIENDO,
    BAJANDO
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
    void saltar();

    void establecerLimites(int ancho, int alto);

    void setColision(ObjetoJuego* otro) override;  // CORREGIDO: Declaración correcta

private:
    int cuadroActual;
    int anchoCuadro;
    int altoCuadro;
    int cuadrosPorFila;
    int velocidadAnimacion;
    int contadorAnimacion;
    DireccionMovimiento direccionActual;
    DireccionMovimiento ultimaDireccion;

    int limiteAncho;
    int limiteAlto;

    bool moviendose;
    int tiempoQuieto;
    float velocidadMovimiento;

    EstadoSalto estadoSalto;
    float alturaSaltoMax;
    float velocidadSalto;
    float posicionYInicial;

    void cambiarDireccion(DireccionMovimiento nuevaDireccion);
    int obtenerIndiceCuadro(DireccionMovimiento direccion, int frame);
    void manejarSalto(float tiempo);
};

#endif // GOKU_H
