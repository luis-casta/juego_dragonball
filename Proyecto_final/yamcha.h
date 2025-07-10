#ifndef YAMCHA_H
#define YAMCHA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Yamcha : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Yamcha(qreal x, qreal y, QGraphicsItem* parent = nullptr);

    // Movimiento básico
    void moverIzquierda();
    void moverDerecha();
    void detener();
    void saltar();

    // Ataque
    void atacarAGoku(QGraphicsItem* goku);

    // Vida
    void recibirDanio(int cantidad);
    int getVida() const;
    void setVida(int nuevaVida);

    // Velocidad
    qreal getVelocidad() const;
    void setVelocidad(qreal nuevaVelocidad);

    // Dirección
    int getDireccion() const;
    void setDireccion(int nuevaDireccion);

signals:
    void yamchaDerrotado();

public slots:
    void actualizarMovimiento();

private:
    // Atributos básicos
    int vida;
    qreal velocidad;
    int direccion; // -1: izquierda, 1: derecha, 0: quieto

    // Físicas
    qreal vx, vy, ax;
    bool enElAire;

    // Timer
    QTimer* timerMovimiento;
};

#endif // YAMCHA_H
