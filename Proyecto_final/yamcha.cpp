#include "yamcha.h"

Yamcha::Yamcha(qreal x, qreal y, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent), vida(5), velocidad(2.0), direccion(0)
{
    setPixmap(QPixmap(":/imagenes/yamcha.png").scaled(60, 80));
    setPos(x, y);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Yamcha::actualizarMovimiento);
    timerMovimiento->start(30);
}

void Yamcha::moverIzquierda() { direccion = -1; }
void Yamcha::moverDerecha()   { direccion = 1; }
void Yamcha::detener()        { direccion = 0; }

void Yamcha::actualizarMovimiento() {
    if (direccion != 0) {
        setX(x() + direccion * velocidad);
        // Aquí puedes agregar límites de movimiento si lo deseas
    }
}

void Yamcha::recibirDanio(int cantidad) {
    vida -= cantidad;
    if (vida <= 0) {
        emit yamchaDerrotado();
        // Aquí puedes agregar animación de derrota o eliminarlo de la escena
    }
}

// Getters y setters
int Yamcha::getVida() const { return vida; }
void Yamcha::setVida(int nuevaVida) { vida = nuevaVida; }

qreal Yamcha::getVelocidad() const { return velocidad; }
void Yamcha::setVelocidad(qreal nuevaVelocidad) { velocidad = nuevaVelocidad; }

int Yamcha::getDireccion() const { return direccion; }
void Yamcha::setDireccion(int nuevaDireccion) { direccion = nuevaDireccion; }
