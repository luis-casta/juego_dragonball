#ifndef BARRAVIDA_H
#define BARRAVIDA_H

#include <QGraphicsRectItem>

class BarraVida : public QGraphicsRectItem
{
public:
    BarraVida(QGraphicsItem* parent = nullptr);

    void actualizarVida(int vidaActual, int vidaMaxima);
};

#endif // BARRAVIDA_H
