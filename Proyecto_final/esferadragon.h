#ifndef ESFERADRAGON_H
#define ESFERADRAGON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>//para la estrella
#include <QFont>//para la estrella
#include <QTimer>
#include <QtMath>
#include <QBrush>
#include <QPen>
#include <QObject>

class EsferaDragon : public QGraphicsEllipseItem
{
public:
    EsferaDragon(qreal x, qreal y, QGraphicsItem* parent = nullptr)
        : QGraphicsEllipseItem(0, 0, 20, 20, parent), baseY(y), t(0)
    {
        setBrush(QBrush(Qt::yellow));
        setPen(QPen(Qt::darkYellow, 2));
        setPos(x, y);

        estrella = new QGraphicsTextItem("★", this);
        estrella->setDefaultTextColor(Qt::red);
        estrella->setFont(QFont("Arial", 10, QFont::Bold));
        estrella->setPos(0,0); // Centrada en la esfera

        timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [this]() { flotar(); });
        timer->start(16);
    }

    ~EsferaDragon() {
        delete timer;
    }

    void flotar() {
        t += 0.05;
        setY(baseY + 10 * qSin(t));
    }

private:
    qreal baseY, t;
    QTimer* timer;
    QGraphicsTextItem* estrella;
};

#endif // ESFERADRAGON_H
