#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>


class BarraVida : public QGraphicsRectItem
{
public:
    BarraVida(QGraphicsItem* parent = nullptr)
        : QGraphicsRectItem(parent)
    {
        setRect(0, 0, 100, 10);  // Tamaño inicial
        setBrush(QBrush(Qt::red));
        setPen(Qt::NoPen);
    }

    void actualizarVida(int vidaActual, int vidaMaxima)
    {
        qreal porcentaje = qreal(vidaActual) / vidaMaxima;
        setRect(0, 0, 100 * porcentaje, 10);
    }
};
