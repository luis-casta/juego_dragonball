#include "yamcha.h"
#include "proyectil.h"
#include <cmath>
#include <QGraphicsScene>
Yamcha::Yamcha(qreal x, qreal y, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent), vida(5), velocidad(2.0), direccion(0), vx(0), vy(0), ax(0), enElAire(false)
{
    // Cargar sprite de Yamcha
    setPixmap(QPixmap(":/imagenes/yamcha.png").scaled(60, 80)); // Ajusta la ruta y tamaño según tu sprite
    setPos(x, y);

    // Timer para actualizar movimiento y físicas
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Yamcha::actualizarMovimiento);
    timerMovimiento->start(30); // Actualiza cada 30 ms
}

void Yamcha::moverIzquierda()
{
    direccion = -1;
}

void Yamcha::moverDerecha()
{
    direccion = 1;
}

void Yamcha::detener()
{
    direccion = 0;
}

void Yamcha::actualizarMovimiento()
{
    // Movimiento horizontal con aceleración
    if (direccion != 0) {
        vx += direccion * 0.5; // aceleración
        if (vx > velocidad) vx = velocidad;
        if (vx < -velocidad) vx = -velocidad;
    } else {
        vx *= 0.8; // fricción
    }

    setX(x() + vx);

    // Salto y gravedad
    if (enElAire) {
        vy += 0.5; // gravedad
        setY(y() + vy);

        // Si toca el suelo
        if (y() >= 500) { // Ajusta según tu suelo
            setY(500);
            vy = 0;
            enElAire = false;
        }
    }

    // Límites de pantalla
    if (x() < 0) setX(0);
    if (x() > 740) setX(740); // 800 - 60 (ancho de Yamcha)
}

void Yamcha::saltar()
{
    if (!enElAire) {
        vy = -10; // velocidad inicial de salto
        enElAire = true;
    }
}

void Yamcha::atacarAGoku(QGraphicsItem* goku)
{
    if (!scene() || !goku) return;

    qreal dx = goku->x() - this->x();
    qreal dy = goku->y() - this->y();
    qreal distancia = sqrt(dx*dx + dy*dy);

    // Solo atacar si Goku está a una distancia razonable
    if (distancia > 400) return;

    qreal velocidad = 8.0;
    qreal vx = velocidad * (dx / distancia);
    qreal vy = velocidad * (dy / distancia) - 5.0; // -5 para parábola

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

// Getters y setters
int Yamcha::getVida() const
{
    return vida;
}

void Yamcha::setVida(int nuevaVida)
{
    vida = nuevaVida;
}

qreal Yamcha::getVelocidad() const
{
    return velocidad;
}

void Yamcha::setVelocidad(qreal nuevaVelocidad)
{
    velocidad = nuevaVelocidad;
}

int Yamcha::getDireccion() const
{
    return direccion;
}

void Yamcha::setDireccion(int nuevaDireccion)
{
    direccion = nuevaDireccion;
}
