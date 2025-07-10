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

    void moverIzquierda();
    void moverDerecha();
    void detener();
    void saltar();

    void atacarAGoku(QGraphicsItem* goku);

    void recibirDanio(int cantidad);
    int getVida() const;
    void setVida(int nuevaVida);

    void iniciarAtaque();

signals:
    void yamchaDerrotado();

public slots:
    void actualizarMovimiento();
    void actualizarAnimacion();

private:
    int vida;
    qreal velocidad;
    int direccion; // -1 izquierda, 1 derecha, 0 quieto

    qreal vx, vy;
    bool enElAire;

    QTimer* timerMovimiento;
    QTimer* timerAnimacion;

    QPixmap spriteSheet;
    int frameActual;
    int columnas;
    int filas;
    int anchoFrame;
    int altoFrame;

    // Variables para animación de ataque
    bool atacando;
    int animacionAtaqueFila;
    int animacionAtaqueInicioCol;
    int animacionAtaqueFinCol;
    int frameActualAtaque;
};

#endif // YAMCHA_H
