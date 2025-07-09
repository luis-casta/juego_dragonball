#include "areajuego.h"
#include <QPainter>
#include <QDebug>
#include <QColor>

AreaJuego::AreaJuego(QWidget* parent)
    : QWidget(parent)
{
    goku = new Goku(100, 100, ":/imagenes/spritegoku.png");  // Con :/imagenes/

    if (fondo.load(":/imagenes/escena1.png")) {              // Con :/imagenes/
        qDebug() << "Fondo cargado correctamente";
        qDebug() << "Tamaño del fondo:" << fondo.width() << "x" << fondo.height();
    } else {
        qDebug() << "ERROR: No se pudo cargar el fondo";
    }
}
AreaJuego::~AreaJuego()
{
    if (goku) {
        delete goku;
        goku = nullptr;
    }
}

void AreaJuego::cambiarFondo(const QString& archivoFondo)
{
    fondo.load(archivoFondo);
    update();
}

void AreaJuego::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    qDebug() << "paintEvent llamado - Area:" << width() << "x" << height();

    if (!fondo.isNull()) {
        int fondoX = (width() - fondo.width()) / 2;
        int fondoY = (height() - fondo.height()) / 2;

        if (fondo.width() < width() && fondo.height() < height()) {
            painter.drawPixmap(fondoX, fondoY, fondo);
        } else {
            QPixmap fondoEscalado = fondo.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            int escX = (width() - fondoEscalado.width()) / 2;
            int escY = (height() - fondoEscalado.height()) / 2;
            painter.drawPixmap(escX, escY, fondoEscalado);
        }

        qDebug() << "Fondo dibujado";
    } else {
        qDebug() << "Fondo es null - dibujando color de respaldo";
        painter.fillRect(rect(), QColor(173, 216, 230));
    }

    if (goku) {
        goku->dibujar(painter);
    } else {
        qDebug() << "Goku es null";
    }
}
