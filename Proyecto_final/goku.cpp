#include "goku.h"
#include <QGraphicsScene>
#include "plataforma.h"
#include"yamcha.h"

Goku::Goku()
    : frameActual(0), anchoCuadro(61), altoCuadro(79), totalFrames(11),
    velocidadAnimacion(5), contadorAnimacion(0), dx(0),
    saltando(false), agachado(false), velocidadSalto(13), alturaSaltoMax(150), puedeSaltar(true), dy(0),vidas(3)

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
void Goku::atacar(Yamcha* yamcha)
{
    if (!yamcha) return;

    // Distancia horizontal para verificar si Yamcha está en rango de ataque
    qreal distanciaX = std::abs(yamcha->x() - this->x());

    const qreal rangoAtaque = 50.0;  // Ajusta según convenga

    if (distanciaX <= rangoAtaque) {
        yamcha->recibirDanio(2);  // Goku causa 1 punto de daño
    }
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
