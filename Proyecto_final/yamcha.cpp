#include "yamcha.h"
#include "proyectil.h"
#include <cmath>
#include <QGraphicsScene>
#include <QDebug>

Yamcha::Yamcha(qreal x, qreal y, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent), vida(5), velocidad(2.0), direccion(0), vx(0), vy(0), enElAire(false),
    frameActual(0), columnas(9), filas(5),
    atacando(false), animacionAtaqueFila(3), animacionAtaqueInicioCol(3), animacionAtaqueFinCol(6), frameActualAtaque(3)
{
    qDebug() << "Yamcha creado en posición:" << x << y;

    spriteSheet = QPixmap(":/imagenes/yamchaa.png");
    if (spriteSheet.isNull()) {
        qDebug() << "Error: No se pudo cargar el sprite yamchaa.png";
    }
    anchoFrame = spriteSheet.width() / columnas;
    altoFrame = spriteSheet.height() / filas;

    setPixmap(spriteSheet.copy(0, 0, anchoFrame, altoFrame));
    setPos(x, y);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Yamcha::actualizarMovimiento);
    timerMovimiento->start(30);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Yamcha::actualizarAnimacion);
    timerAnimacion->start(120);
}

void Yamcha::moverIzquierda() { direccion = -1; }
void Yamcha::moverDerecha() { direccion = 1; }
void Yamcha::detener() { direccion = 0; }

void Yamcha::actualizarMovimiento()
{
    if (direccion != 0) {
        vx += direccion * 0.5;
        if (vx > velocidad) vx = velocidad;
        if (vx < -velocidad) vx = -velocidad;
    } else {
        vx *= 0.8;
    }

    setX(x() + vx);

    if (enElAire) {
        vy += 0.5;
        setY(y() + vy);
        if (y() >= 500) {
            setY(500);
            vy = 0;
            enElAire = false;
        }
    }

    if (x() < 0) setX(0);
    if (x() > 720) setX(720);
}

void Yamcha::actualizarAnimacion()
{
    if (atacando) {
        setPixmap(spriteSheet.copy(frameActualAtaque * anchoFrame, animacionAtaqueFila * altoFrame, anchoFrame, altoFrame));
        frameActualAtaque++;
        if (frameActualAtaque > animacionAtaqueFinCol) {
            frameActualAtaque = animacionAtaqueInicioCol;
            atacando = false;  // Termina la animación de ataque
        }
    } else {
        int fila = 0;
        if (direccion == 1) fila = 0;       // caminar derecha
        else if (direccion == -1) fila = 1; // caminar izquierda
        else {
            fila = 0;
            frameActual = 0;
        }

        if (direccion != 0)
            frameActual = (frameActual + 1) % columnas;

        int xFrame = frameActual * anchoFrame;
        int yFrame = fila * altoFrame;

        setPixmap(spriteSheet.copy(xFrame, yFrame, anchoFrame, altoFrame));
    }
}

void Yamcha::saltar()
{
    if (!enElAire) {
        vy = -10;
        enElAire = true;
    }
}

void Yamcha::iniciarAtaque()
{
    atacando = true;
    frameActualAtaque = animacionAtaqueInicioCol;
}

void Yamcha::atacarAGoku(QGraphicsItem* goku)
{
    if (!scene() || !goku) return;

    qreal dx = goku->x() - this->x();
    qreal dy = goku->y() - this->y();
    qreal distancia = sqrt(dx*dx + dy*dy);

    if (distancia > 400) return;

    // Iniciar animación de ataque
    iniciarAtaque();

    qreal velocidad = 8.0;
    qreal vx = velocidad * (dx / distancia);
    qreal vy = velocidad * (dy / distancia) - 5.0;

    Proyectil* proyectil = new Proyectil(this->x() + 30, this->y() + 20, vx, vy, DeYamcha);
    scene()->addItem(proyectil);
}

void Yamcha::recibirDanio(int cantidad)
{
    vida -= cantidad;
    if (vida <= 0) {
        emit yamchaDerrotado();
    }
}

int Yamcha::getVida() const { return vida; }
void Yamcha::setVida(int nuevaVida) { vida = nuevaVida; }
