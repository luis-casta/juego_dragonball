#ifndef YAMCHA_H
#define YAMCHA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

struct Animacion {
    int fila;
    int columnaInicio;
    int columnaFin;
};

class Yamcha : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Yamcha(qreal x, qreal y, QGraphicsItem* parent = nullptr);

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
    int direccion; // -1 izquierda, 1 derecha, 0 quieto

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

    // ELIMINADO: const int offsetY = 15; // Ya no es necesario
};

#endif // YAMCHA_H
