#include "barravida.h"
#include <QBrush>
#include <QPen>

BarraVida::BarraVida(QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{
    setRect(0, 0, 100, 10);  // Tamaño inicial
    setBrush(QBrush(Qt::red));
    setPen(Qt::NoPen);
}

void BarraVida::actualizarVida(int vidaActual, int vidaMaxima)
{
    if (vidaMaxima <= 0) return;

    qreal porcentaje = (vidaActual * 1.0) / vidaMaxima;
    if (porcentaje < 0) porcentaje = 0;
    if (porcentaje > 1) porcentaje = 1;

    setRect(0, 0, 100 * porcentaje, 10);
}
