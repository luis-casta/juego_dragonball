#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QtMath>
#include <QBrush>
#include <QObject>

class PlataformaFlotante : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    PlataformaFlotante(qreal x, qreal y, qreal amplitud, qreal frecuencia, bool moverX, bool moverY, QGraphicsItem* parent = nullptr);
    ~PlataformaFlotante();

    QPointF getPosAnterior() const { return posAnterior; }

public slots:
    void mover();

private:
    qreal posX, posY, A, w, t;
    bool moverEnX;
    bool moverEnY;
    QTimer* timer;
    QPointF posAnterior;
};

#endif // PLATAFORMA_H
