#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QtMath>
#include <QBrush>
#include <QObject>

class PlataformaFlotante : public QGraphicsRectItem
{
public:
    PlataformaFlotante(qreal x, qreal y, qreal amplitud, qreal frecuencia, QGraphicsItem* parent = nullptr)
        : QGraphicsRectItem(0, 0, 80, 20, parent), posX(x), posY(y), A(amplitud), w(frecuencia), t(0)
    {
        setBrush(QBrush(QColor(160, 82, 45))); // Color plataforma
        setPos(posX, posY);

        timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [this]() { mover(); });
        timer->start(16);
    }

    ~PlataformaFlotante() {
        delete timer;
    }

    void mover() {
        t += 0.05;
        setY(posY + A * qSin(w * t));
    }

private:
    qreal posX, posY, A, w, t;
    QTimer* timer;
};

#endif // PLATAFORMA_H
