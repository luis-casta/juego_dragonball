#include "goku.h"
#include <QGraphicsScene>

Goku::Goku()
    : frameActual(0), anchoCuadro(61), altoCuadro(79), totalFrames(11),
    velocidadAnimacion(5), contadorAnimacion(0), dx(0),
    saltando(false), agachado(false), velocidadSalto(8), alturaSaltoMax(150), dy(0)
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

void Goku::moverIzquierda()
{
    if (!agachado)
        dx = -5;
}

void Goku::moverDerecha()
{
    if (!agachado)
        dx = 5;
}

void Goku::detenerMovimiento()
{
    dx = 0;
}

void Goku::saltar()
{
    if (!saltando && !agachado) {
        saltando = true;
        dy = -velocidadSalto;
        posicionYInicial = y();
    }
}

void Goku::agacharse()
{
    agachado = true;
    dx = 0;  // No se mueve agachado
    frameActual = 0;  // Reiniciar animación
}

void Goku::levantarse()
{
    agachado = false;
    frameActual = 0;
}

void Goku::actualizarAnimacion()
{
    QRectF limites = scene()->sceneRect();

    qreal nuevaX = x() + dx;

    if (nuevaX < limites.left())
        nuevaX = limites.left();
    else if (nuevaX + anchoCuadro > limites.right())
        nuevaX = limites.right() - anchoCuadro;

    setX(nuevaX);

    if (saltando) {
        qreal nuevaY = y() + dy;

        if (nuevaY <= posicionYInicial - alturaSaltoMax) {
            dy = velocidadSalto;
        }
        if (nuevaY >= posicionYInicial) {
            nuevaY = posicionYInicial;
            saltando = false;
            dy = 0;
        }
        setY(nuevaY);
    }

    if (agachado) {
        // Mostrar sprite de agachado fila 4, columna 6
        int xFrame = 6 * anchoCuadro;
        int yFrame = 4 * altoCuadro;
        setPixmap(spriteSheet.copy(xFrame, yFrame, anchoCuadro, altoCuadro));
        return;  // No animar más mientras está agachado
    }

    if (dx != 0) {
        contadorAnimacion++;
        if (contadorAnimacion >= velocidadAnimacion) {
            frameActual = (frameActual + 1) % totalFrames;
            contadorAnimacion = 0;
        }
    } else {
        frameActual = 0;
    }

    int fila = (dx >= 0) ? 2 : 1;

    int xFrame = frameActual * anchoCuadro;
    int yFrame = fila * altoCuadro;

    setPixmap(spriteSheet.copy(xFrame, yFrame, anchoCuadro, altoCuadro));
}
