#include "goku.h"
#include <QKeyEvent>

Goku::Goku()
    : frameActual(0), anchoCuadro(61), altoCuadro(73), cuadrosPorFila(11),
    velocidadAnimacion(8), contadorAnimacion(0), dx(0),
    saltando(false), velocidadSalto(6), alturaSaltoMax(100), dy(0)
{
    spriteSheet.load(":/imagenes/spritegoku.png");
    setPixmap(spriteSheet.copy(0, 0, anchoCuadro, altoCuadro));

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    posicionYInicial = y();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Goku::actualizarAnimacion);
    timer->start(16);
}

void Goku::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        dx = -4;
        break;
    case Qt::Key_Right:
        dx = 4;
        break;
    case Qt::Key_Space:
        if (!saltando) {
            saltando = true;
            dy = -velocidadSalto;
            posicionYInicial = y();
        }
        break;
    }
}

void Goku::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
        dx = 0;
        break;
    }
}

void Goku::actualizarAnimacion()
{
    // Movimiento horizontal
    moveBy(dx, 0);

    // Movimiento salto
    if (saltando) {
        moveBy(0, dy);
        if (y() <= posicionYInicial - alturaSaltoMax) {
            dy = velocidadSalto;
        }
        if (y() >= posicionYInicial) {
            setY(posicionYInicial);
            saltando = false;
            dy = 0;
        }
    }

    // Animación
    if (dx != 0) {
        contadorAnimacion++;
        if (contadorAnimacion >= velocidadAnimacion) {
            frameActual = (frameActual + 1) % 4;
            contadorAnimacion = 0;
        }
    } else {
        frameActual = 0;
    }

    int fila = (dx >= 0) ? 2 : 1;
    int x = frameActual * anchoCuadro;
    int y = fila * altoCuadro;

    setPixmap(spriteSheet.copy(x, y, anchoCuadro, altoCuadro));
}

void Goku::moverIzquierda()
{
    dx = -4;
}

void Goku::moverDerecha()
{
    dx = 4;
}

void Goku::detenerMovimiento()
{
    dx = 0;
}

void Goku::saltar()
{
    if (!saltando) {
        saltando = true;
        dy = -velocidadSalto;
        posicionYInicial = y();
    }
}
