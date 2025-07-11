#ifndef YAMCHA_H
#define YAMCHA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "barravida.h"

struct Animacion {
    int fila;
    int columnaInicio;
    int columnaFin;
};

class Yamcha : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Yamcha(qreal x, qreal y, QGraphicsItem* parent = nullptr);
    BarraVida* barraVida;
    int vidaMaxima;

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

private slots:
    void actualizarMovimiento();
    void actualizarAnimacion();

private:
    void configurarAnimaciones();
    void mostrarFrame(int fila, int columna);

    int vida;
    qreal velocidad;
    int direccion;

    qreal vx;
    qreal vy;
    bool enElAire;

    QTimer* timerMovimiento;
    QTimer* timerAnimacion;

    QPixmap spriteSheet;

    int frameActual;
    int frameActualAtaque;
    int contadorFrames;

    bool atacando;

    Animacion animacionQuieto;
    Animacion animacionCaminar;
    Animacion animacionAtaque;
    Animacion animacionSalto;

};

#endif // YAMCHA_H
