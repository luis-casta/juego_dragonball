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

    // Configuración del sprite 17x17 (64x64 cada frame)
    static const int TOTAL_COLUMNAS = 17;
    static const int TOTAL_FILAS = 17;
    static const int ANCHO_FRAME = 64;
    static const int ALTO_FRAME = 64;

    // Configuración de animaciones
    struct AnimacionConfig {
        int fila;
        int columnaInicio;
        int columnaFin;
    };

    AnimacionConfig animacionQuieto;
    AnimacionConfig animacionCaminar;
    AnimacionConfig animacionAtaque;
    AnimacionConfig animacionSalto;

    // Estado de animación
    bool atacando;
    int frameActualAtaque;
    int contadorFrames;

    void configurarAnimaciones();
    void mostrarFrame(int fila, int columna);
};

#endif // YAMCHA_H
