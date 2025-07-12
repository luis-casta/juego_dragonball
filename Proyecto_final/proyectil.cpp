#include "proyectil.h"
#include "qgraphicsscene.h"
#include <cmath>

// Constructor para proyectiles aleatorios que caen del cielo
Proyectil::Proyectil(qreal origenX, qreal origenY, qreal destinoX, qreal destinoY, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent), tipo(Aleatorio)
{
    setPos(origenX, origenY);

    // Calcular velocidad hacia el destino
    qreal dx = destinoX - origenX;
    qreal dy = destinoY - origenY;
    qreal distancia = sqrt(dx*dx + dy*dy);

    qreal velocidad = 3.0; // Velocidad para proyectiles aleatorios
    vx = velocidad * (dx / distancia);
    vy = velocidad * (dy / distancia);

    inicializar();
}

// Constructor para proyectiles dirigidos con velocidad
Proyectil::Proyectil(qreal x, qreal y, qreal vx_, qreal vy_, TipoProyectil tipo_, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent), vx(vx_), vy(vy_), tipo(tipo_)
{
    setPos(x, y);
    inicializar();
}

void Proyectil::inicializar()
{
    QPixmap spriteSheet(":/imagenes/proyectil.png"); // 500x500 px
    int columnas = 5;
    int filas = 5;
    int anchoFrame = spriteSheet.width() / columnas;
    int altoFrame = spriteSheet.height() / filas;

    // Primer frame (columna 0, fila 0)
    QPixmap frameProyectil = spriteSheet.copy(0, 0, anchoFrame, altoFrame);
    setPixmap(frameProyectil);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Proyectil::actualizar);
    timer->start(16);
}

void Proyectil::actualizar()
{
    if (tipo == DeYamcha) {
        // Proyectiles de Yamcha con gravedad (parábola)
        const qreal gravedad = 0.5;
        vy += gravedad;
    } else if (tipo == Aleatorio) {
        // Proyectiles aleatorios sin gravedad
        // vx y vy se mantienen constantes
    }

    setPos(x() + vx, y() + vy);
}

TipoProyectil Proyectil::getTipo() const
{
    return tipo;
}
