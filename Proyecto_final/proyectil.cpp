#include "proyectil.h"
#include <QtMath>
#include <QPainter>
#include <QRandomGenerator>

Proyectil::Proyectil(qreal x, qreal y, qreal destinoX, qreal destinoY)
    : vx(0), vy(0), g(0.5), danio(1)
{
    // Sprite sheet: 4 columnas, 5 filas
    QPixmap spriteSheet(":/imagenes/proyectil.png");
    int columnas = 4;
    int filas = 5;
    int frameW = spriteSheet.width() / columnas;
    int frameH = spriteSheet.height() / filas;

    // Elegir frame aleatorio
    int row = QRandomGenerator::global()->bounded(filas); // fila aleatoria de 0 a 4
    int col = 0; // siempre la primera columna

    QPixmap framePixmap;
    if (!spriteSheet.isNull()) {
        framePixmap = spriteSheet.copy(col * frameW, row * frameH, frameW, frameH)
        .scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    setPixmap(framePixmap);
    setPos(x, y);

    // Calcula la velocidad inicial para llegar a destinoX, destinoY
    qreal dx = destinoX - x;
    qreal dy = destinoY - y;
    qreal t = qAbs(dx) / 4.0; //vel en x
    if (t < 1) t = 1; // Evita división por cero o valores muy pequeños

    vx = dx / t;
    vy = (dy + 0.5 * g * t * t) / t;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Proyectil::mover);
    timer->start(16);
}

void Proyectil::mover()
{
    setPos(x() + vx, y() + vy);
    vy += g;

    // Elimina el proyectil si sale de la pantalla
    // if (x() < 0 || x() > 820 || y() > 620) {
    //     deleteLater();}

}
