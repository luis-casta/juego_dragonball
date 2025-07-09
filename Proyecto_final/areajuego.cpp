#include "areajuego.h"
#include <QPainter>
#include <QDebug>
#include <QColor>
#include <QKeyEvent>  // AGREGAR ESTA LÍNEA

AreaJuego::AreaJuego(QWidget* parent)
    : QWidget(parent)
{
    goku = new Goku(100, 100, ":/imagenes/spritegoku.png");

    setFocusPolicy(Qt::StrongFocus);

    if (fondo.load(":/imagenes/escena1.png")) {
        qDebug() << "Fondo cargado correctamente";

        // Establecer límites basados en el tamaño del fondo
        if (goku) {
            goku->establecerLimites(fondo.width(), fondo.height());
        }
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

void AreaJuego::keyPressEvent(QKeyEvent* event)
{
    if (goku) {
        switch (event->key()) {
        case Qt::Key_Left:
        case Qt::Key_A:
            goku->moverIzquierda();
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            goku->moverDerecha();
            break;
        case Qt::Key_Up:
        case Qt::Key_W:
            goku->moverArriba();
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            goku->moverAbajo();
            break;
        }
        update();
    }

    QWidget::keyPressEvent(event);
}

void AreaJuego::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);

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
    } else {
        painter.fillRect(rect(), QColor(173, 216, 230));
    }

    if (goku) {
        goku->dibujar(painter);
    }
}
