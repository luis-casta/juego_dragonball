#ifndef ESFERADRAGON_H
#define ESFERADRAGON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <QTimer>
#include <QtMath>
#include <QBrush>
#include <QPen>
#include <QObject>

class EsferaDragon : public QGraphicsEllipseItem
{
public:
    EsferaDragon(qreal x, qreal y, QGraphicsItem* parent = nullptr)
        : QGraphicsEllipseItem(0, 0, 20, 20, parent),
        baseY(y), t(0), tHorizontal(0)
    {
        setBrush(QBrush(Qt::yellow));
        setPen(QPen(Qt::darkYellow, 2));
        setPos(x, y);

        estrella = new QGraphicsTextItem("★", this);
        estrella->setDefaultTextColor(Qt::red);
        estrella->setFont(QFont("Arial", 10, QFont::Bold));
        estrella->setPos(0, 0);

        timer = new QTimer();

        QObject::connect(timer, &QTimer::timeout,[this]() { mover(); });

        timer->start(16);
    }

    ~EsferaDragon() {
        if (timer) {
            timer->stop();
            delete timer;
        }
    }

    void mover() {
        // Movimiento vertical
        t += 0.05;
        qreal offsetY = 10 * qSin(t);

        // Movimiento horizontal senoidal por toda la escena
        tHorizontal += 0.02; // Velocidad del movimiento horizontal
        qreal amplitudX = 350; // (800 - 100) / 2
        qreal centroX = 400;   // Centro de la escena (800 / 2)

        qreal nuevaX = centroX + amplitudX * qSin(tHorizontal);
        qreal nuevaY = baseY + offsetY;

        setPos(nuevaX, nuevaY);
    }

private:
    qreal baseY, t, tHorizontal;
    QTimer* timer;
    QGraphicsTextItem* estrella;
};

#endif // ESFERADRAGON_H

