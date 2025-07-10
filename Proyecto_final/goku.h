#ifndef GOKU_H
#define GOKU_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "yamcha.h"

class Goku : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Goku();

    void moverIzquierda();
    void moverDerecha();
    void detenerMovimiento();
    void saltar();
    void agacharse();
    void levantarse();
    int getVidas() const { return vidas; }
    void perderVida() { if (vidas > 0) vidas--; }
    void reiniciarVidas() { vidas = 5; }
    void atacar(Yamcha* yamcha);

public slots:
    void actualizarAnimacion();

private:
    QPixmap spriteSheet;
    int frameActual;
    int anchoCuadro;
    int altoCuadro;
    int totalFrames;
    int velocidadAnimacion;
    int contadorAnimacion;

    int dx;
    bool saltando;
    bool agachado;
    float velocidadSalto;
    float alturaSaltoMax;
    float posicionYInicial;
    bool puedeSaltar;
    float dy;
    int vidas;

};

#endif // GOKU_H
