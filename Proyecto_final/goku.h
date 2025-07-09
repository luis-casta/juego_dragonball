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

public slots:
    void actualizarAnimacion();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QPixmap spriteSheet;
    int frameActual;
    int anchoCuadro;
    int altoCuadro;
    int cuadrosPorFila;
    int velocidadAnimacion;
    int contadorAnimacion;

    int dx;  // Movimiento horizontal

    // Variables para salto
    bool saltando;
    float velocidadSalto;
    float alturaSaltoMax;
    float posicionYInicial;
    float dy;  // Movimiento vertical
};

#endif // GOKU_H
