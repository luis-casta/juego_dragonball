#include "plataforma.h"

PlataformaFlotante::PlataformaFlotante(qreal x, qreal y, qreal amplitud, qreal frecuencia, bool moverX, bool moverY, QGraphicsItem* parent)
    : QObject(), QGraphicsRectItem(0, 0, 60, 20, parent), posX(x), posY(y), A(amplitud), w(frecuencia), t(0), moverEnX(moverX), moverEnY(moverY)
{
    setBrush(QBrush(QColor(160, 82, 45))); // Color plataforma
    setPos(posX, posY);
    posAnterior = pos();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PlataformaFlotante::mover);
    timer->start(16);
}

PlataformaFlotante::~PlataformaFlotante()
{}

void PlataformaFlotante::mover()
{
    t += 0.05;
    qreal nuevoX = posX;
    qreal nuevoY = posY;

    if (moverEnX)
        nuevoX = posX + A * qSin(w * t);
    if (moverEnY)
        nuevoY = posY + A * qCos(w * t);

    QPointF nuevaPos(nuevoX, nuevoY);
    setPos(nuevaPos);
}
