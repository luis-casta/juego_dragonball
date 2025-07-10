#include "yamcha.h"
#include "proyectil.h"
#include <cmath>
#include <QGraphicsScene>

const int TOTAL_FILAS = 4;
const int TOTAL_COLUMNAS = 3;
const int ANCHO_FRAME = 106;  // 318 / 3
const int ALTO_FRAME = 104;   // 419 / 4

Yamcha::Yamcha(qreal x, qreal y, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent),
    vida(5),
    velocidad(2.0),
    direccion(0),
    vx(0),
    vy(0),
    enElAire(false),
    frameActual(0),
    frameActualAtaque(0),
    contadorFrames(0),
    atacando(false)
{
    spriteSheet = QPixmap(":/imagenes/yamchaa.png");
    if (spriteSheet.isNull()) {
        return;
    }

    configurarAnimaciones();

    mostrarFrame(animacionQuieto.fila, animacionQuieto.columnaInicio);
    setPos(x, y);

    setVisible(true);
    setZValue(1);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Yamcha::actualizarMovimiento);
    timerMovimiento->start(30);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Yamcha::actualizarAnimacion);
    timerAnimacion->start(120);
}

void Yamcha::configurarAnimaciones()
{
    animacionQuieto = {0, 0, 0};
    animacionCaminar = {0, 0, 2};
    animacionAtaque = {1, 0, 2};
    animacionSalto = {2, 0, 2};
}

void Yamcha::mostrarFrame(int fila, int columna)
{
    if (fila < 0 || fila >= TOTAL_FILAS || columna < 0 || columna >= TOTAL_COLUMNAS) {
        return;
    }

    int xFrame = columna * ANCHO_FRAME;
    int yFrame = fila * ALTO_FRAME;

    QPixmap frame = spriteSheet.copy(xFrame, yFrame, ANCHO_FRAME, ALTO_FRAME);

    // Escalar para que se vea más grande (ajusta tamaño si quieres)
    QPixmap frameEscalado = frame.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(frameEscalado);
    update();
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

    if (x() < 0) setX(0);
    if (x() + 80 > 800) setX(800 - 80);

    if (enElAire) {
        vy += 0.5;
        setY(y() + vy);
        if (y() >= 420) {
            setY(420);
            vy = 0;
            enElAire = false;
        }
    } else {
        if (y() != 420) setY(420);
    }
}

void Yamcha::actualizarAnimacion()
{
    contadorFrames++;

    if (atacando) {
        if (contadorFrames % 6 == 0) {
            frameActualAtaque++;
            if (frameActualAtaque > animacionAtaque.columnaFin) {
                frameActualAtaque = animacionAtaque.columnaInicio;
                atacando = false;
            }
        }
        mostrarFrame(animacionAtaque.fila, frameActualAtaque);

    } else if (enElAire) {
        int frameSalto = animacionSalto.columnaInicio + (contadorFrames / 8) %
                                                            (animacionSalto.columnaFin - animacionSalto.columnaInicio + 1);
        mostrarFrame(animacionSalto.fila, frameSalto);

    } else if (direccion != 0) {
        if (contadorFrames % 4 == 0) {
            frameActual++;
            if (frameActual > animacionCaminar.columnaFin) {
                frameActual = animacionCaminar.columnaInicio;
            }
        }
        mostrarFrame(animacionCaminar.fila, frameActual);

    } else {
        mostrarFrame(animacionQuieto.fila, animacionQuieto.columnaInicio);
        frameActual = animacionCaminar.columnaInicio;
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
    frameActualAtaque = animacionAtaque.columnaInicio;
}

void Yamcha::atacarAGoku(QGraphicsItem* goku)
{
    if (!scene() || !goku) return;

    qreal dx = goku->x() - this->x();
    qreal dy = goku->y() - this->y();
    qreal distancia = sqrt(dx*dx + dy*dy);

    if (distancia > 400) return;

    iniciarAtaque();

    qreal velocidadProyectil = 6.0;
    qreal vxProyectil = velocidadProyectil * (dx / distancia);
    qreal vyProyectil = velocidadProyectil * (dy / distancia) - 2.0;

    Proyectil* proyectil = new Proyectil(this->x() + 40, this->y() + 40, vxProyectil, vyProyectil, DeYamcha);
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
