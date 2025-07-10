#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

enum TipoProyectil {
    DeGoku,
    DeYamcha,
    Aleatorio  // Para los proyectiles que caen del cielo
};

class Proyectil : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // Constructor original (para proyectiles aleatorios que caen)
    Proyectil(qreal origenX, qreal origenY, qreal destinoX, qreal destinoY, QGraphicsItem* parent = nullptr);

    // Constructor nuevo (para proyectiles dirigidos con velocidad)
    Proyectil(qreal x, qreal y, qreal vx, qreal vy, TipoProyectil tipo, QGraphicsItem* parent = nullptr);

    TipoProyectil getTipo() const;

public slots:
    void actualizar();

private:
    qreal vx, vy;
    TipoProyectil tipo;
    QTimer* timer;

    void inicializar();
};

#endif // PROYECTIL_H

