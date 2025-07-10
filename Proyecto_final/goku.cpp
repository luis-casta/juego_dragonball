#include "goku.h"
#include <QGraphicsScene>
#include "plataforma.h"
#include "yamcha.h"
#include <cmath>

Goku::Goku()
    : frameActual(0), anchoCuadro(61), altoCuadro(79), totalFrames(11),
    velocidadAnimacion(10), contadorAnimacion(0), dx(0),
    saltando(false), agachado(false), velocidadSalto(13), alturaSaltoMax(150),
    puedeSaltar(true), dy(0), vidas(3),
    frameActualAtaque(0), atacando(false)
{
    spriteSheet.load(":/imagenes/spritegoku.png");
    setPixmap(spriteSheet.copy(0, 0, anchoCuadro, altoCuadro));

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    posicionYInicial = 500; // del suelo

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Goku::actualizarAnimacion);
    timer->start(16);

    timerAnimacionAtaque = new QTimer(this);
    connect(timerAnimacionAtaque, &QTimer::timeout, this, &Goku::actualizarAnimacionAtaque);
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

void Goku::atacar(Yamcha* yamcha)
{
    if (atacando)
        return; // Ya está atacando, no reiniciar animación

    if (!yamcha)
        return;

    // Distancia horizontal para verificar si Yamcha está en rango de ataque
    qreal distanciaX = std::abs(yamcha->x() - this->x());
    const qreal rangoAtaque = 50.0;  // Ajusta según convenga

    if (distanciaX <= rangoAtaque) {
        yamcha->recibirDanio(2);  // Goku causa 2 puntos de daño
    }

    atacando = true;
    frameActualAtaque = 0;
    timerAnimacionAtaque->start(100); // Cambiar frame cada 100 ms
}

void Goku::actualizarAnimacionAtaque()
{
    if (!atacando)
        return;

    // La fila 2 es índice 1
    int filaAtaque = 2;
    int numFramesAtaque = 4 ; // número de frames en la fila de ataque

    QPixmap frame = spriteSheet.copy(frameActualAtaque * anchoCuadro, filaAtaque * altoCuadro, anchoCuadro, altoCuadro);
    setPixmap(frame);

    frameActualAtaque++;

    if (frameActualAtaque >= numFramesAtaque) {
        timerAnimacionAtaque->stop();
        atacando = false;

        // Volver a imagen normal (fila 2, columna 0) para caminar o idle
        frameActual = 0;
        int filaCaminar = 2;
        setPixmap(spriteSheet.copy(frameActual * anchoCuadro, filaCaminar * altoCuadro, anchoCuadro, altoCuadro));
    }
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
            if (x() + anchoCuadro > plataforma->x() &&
                x() < plataforma->x() + plataforma->rect().width()) {
                plataformaDebajo = plataforma;
                break;
            }
        }
    }

    // Manejar salto PRIMERO
    if (saltando) {
        dy += 0.5; // Gravedad
        qreal nuevaY = y() + dy;

        // Verificar si aterriza en el suelo
        if (nuevaY >= posicionYInicial) {
            nuevaY = posicionYInicial;
            saltando = false;
            dy = 0;
        }

        // Verificar si aterriza en plataforma
        if (plataformaDebajo && dy > 0 && nuevaY + altoCuadro >= plataformaDebajo->y()) {
            nuevaY = plataformaDebajo->y() - altoCuadro + 2;
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
    else {
        // No está saltando - seguir plataforma o aplicar gravedad
        if (plataformaDebajo) {
            // Seguir el movimiento de la plataforma
            qreal nuevaY = plataformaDebajo->y() - altoCuadro + 2;
            setY(nuevaY);
            dy = 0;
        } else {
            // No está sobre plataforma - empezar a caer
            if (y() + altoCuadro < posicionYInicial) {
                saltando = true;
                dy = 2;
            }
        }
    }

    // Si está atacando, no cambiar animación de caminar/agacharse
    if (atacando)
        return;

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
