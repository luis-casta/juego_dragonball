#include "proyectil.h"
#include <QtMath>

Proyectil::Proyectil(qreal x, qreal y, qreal destinoX, qreal destinoY)
    : vx(0), vy(0), g(0.5), danio(1)
{
    // Crear un círculo amarillo como proyectil (puedes cambiarlo por sprite)
    QPixmap proyectilPixmap(20, 20);
    proyectilPixmap.fill(Qt::black);
    setPixmap(proyectilPixmap);
    setPos(x, y);

    // Calcula la velocidad inicial para llegar a destinoX, destinoY
    qreal dx = destinoX - x;
    qreal dy = destinoY - y;
    qreal t = qAbs(dx) / 8.0; // 8 es la velocidad horizontal

    setVX(dx / t);
    setVY((dy + 0.5 * getGravedad() * t * t) / t);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Proyectil::mover);
    timer->start(16);
}

void Proyectil::mover()
{
    setPos(x() + getVX(), y() + getVY());
    setVY(getVY() + getGravedad()); // Aplicar gravedad

    // Elimina el proyectil si sale de la pantalla
    if (x() < 0 || x() > 820 || y() > 620) {
        deleteLater();
    }
}
