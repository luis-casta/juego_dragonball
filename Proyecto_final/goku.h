#ifndef GOKU_H
#define GOKU_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

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

    int dx;  // Movimiento horizontal

    bool saltando;
    bool agachado;
    float velocidadSalto;
    float alturaSaltoMax;
    float posicionYInicial;
    float dy;  // Movimiento vertical
};

#endif // GOKU_H
