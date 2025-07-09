#include "goku.h"
#include <QGraphicsScene>
#include "plataforma.h"

Goku::Goku()
    : frameActual(0), anchoCuadro(61), altoCuadro(79), totalFrames(11),
    velocidadAnimacion(5), contadorAnimacion(0), dx(0),
    saltando(false), agachado(false), velocidadSalto(13), alturaSaltoMax(150), puedeSaltar(true), dy(0)

{
    spriteSheet.load(":/imagenes/spritegoku.png");
    setPixmap(spriteSheet.copy(0, 0, anchoCuadro, altoCuadro));

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    posicionYInicial = 500;//del suelo

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
    if (!saltando) {
        saltando = true;
        dy = -velocidadSalto;
    }
}

void Goku::agacharse()
{
    agachado = true;
    dx = 0;
    frameActual = 0;
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

    // Buscar plataforma debajo de Goku
    PlataformaFlotante* plataformaDebajo = nullptr;
    QList<QGraphicsItem*> itemsDebajo = scene()->items(QRectF(x(), y() + altoCuadro, anchoCuadro, 10));

    for (QGraphicsItem* item : std::as_const(itemsDebajo)) {
        PlataformaFlotante* plataforma = dynamic_cast<PlataformaFlotante*>(item);
        if (plataforma) {
            // Verificar que Goku esté realmente sobre la plataforma
            if (x() + anchoCuadro > plataforma->x() &&
                x() < plataforma->x() + plataforma->rect().width()) {
                plataformaDebajo = plataforma;
                break;
            }
        }
    }

    if (plataformaDebajo) {
        // Está sobre una plataforma - moverse con ella
        qreal nuevaY = plataformaDebajo->y() - altoCuadro + 2;
        setY(nuevaY);
        saltando = false;
        dy = 0;
    } else {
        // No está sobre plataforma - aplicar gravedad
        if (!saltando && y() + altoCuadro < posicionYInicial) {
            saltando = true;
            dy = 2; // Empezar a caer
        }

        if (saltando) {
            dy += 0.5; // Gravedad
            qreal nuevaY = y() + dy;

            // Verificar si aterriza en el suelo
            if (nuevaY >= posicionYInicial) {
                nuevaY = posicionYInicial;
                saltando = false;
                dy = 0;
            }

            // Límite superior
            if (nuevaY < limites.top()) {
                nuevaY = limites.top();
                dy = 2;
            }

            setY(nuevaY);
        }
    }

    // Animación del sprite
    if (agachado) {
        int xFrame = 6 * anchoCuadro;
        int yFrame = 4 * altoCuadro;
        setPixmap(spriteSheet.copy(xFrame, yFrame, anchoCuadro, altoCuadro));
        return;
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

    int fila = 2;
    int xFrame = frameActual * anchoCuadro;
    int yFrame = fila * altoCuadro;

    setPixmap(spriteSheet.copy(xFrame, yFrame, anchoCuadro, altoCuadro));
}
