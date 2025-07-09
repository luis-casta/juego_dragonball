#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Proyectil : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Proyectil(qreal x, qreal y, qreal destinoX, qreal destinoY);

    // Getters
    qreal getVX() const { return vx; }
    qreal getVY() const { return vy; }
    qreal getGravedad() const { return g; }
    int getDanio() const { return danio; }

    // Setters
    void setVX(qreal v) { vx = v; }
    void setVY(qreal v) { vy = v; }
    void setGravedad(qreal gravedad) { g = gravedad; }
    void setDanio(int d) { danio = d; }

public slots:
    void mover();

private:
    qreal vx, vy;
    qreal g;
    int danio;
};

#endif // PROYECTIL_H
