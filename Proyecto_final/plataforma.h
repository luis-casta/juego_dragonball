#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "objetojuego.h"
#include <QTimer>
#include <QtMath>

class PlataformaFlotante : public QObject, public ObjetoJuego
{
    Q_OBJECT
public:
    PlataformaFlotante(qreal x, qreal y, qreal amplitud, qreal frecuencia, QGraphicsItem* parent = nullptr)
        : ObjetoJuego(), posX(x), posY(y), A(amplitud), w(frecuencia), t(0)
    {
        setPixmap(QPixmap(":/imagenes/plataforma.png").scaled(80, 20)); // Usa tu imagen o un rectángulo
        setPos(posX, posY);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &PlataformaFlotante::mover);
        timer->start(16);
    }

public slots:
    void mover() {
        t += 0.05;
        setY(posY + A * qSin(w * t));
    }

private:
    qreal posX, posY, A, w, t;
    QTimer* timer;
};

#endif // PLATAFORMA_H
