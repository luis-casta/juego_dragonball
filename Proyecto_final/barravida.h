#ifndef BARRAVIDA_H
#define BARRAVIDA_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class BarraVida : public QGraphicsRectItem
{
public:
    explicit BarraVida(QGraphicsItem* parent = nullptr)
        : QGraphicsRectItem(parent)
    {
        setRect(0, 0, 100, 10);  // Tamaño inicial
        setBrush(QBrush(Qt::red));
        setPen(Qt::NoPen);
    }

    void actualizarVida(int vidaActual, int vidaMaxima)
    {
        if (vidaMaxima <= 0) return;

        qreal porcentaje = static_cast<qreal>(vidaActual) / vidaMaxima;
        if (porcentaje < 0) porcentaje = 0;
        if (porcentaje > 1) porcentaje = 1;

        setRect(0, 0, 100 * porcentaje, 10);
    }
};

#endif // BARRAVIDA_H
