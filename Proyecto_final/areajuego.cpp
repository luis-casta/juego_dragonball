#include "areajuego.h"
#include <QPainter>
#include <QDebug>
#include <QColor>
#include <QKeyEvent>

AreaJuego::AreaJuego(QWidget* parent)
    : QWidget(parent)
{
    if (!fondo.load(":/imagenes/escena1.png")) {
        qDebug() << "ERROR: No se pudo cargar el fondo";
    } else {
        qDebug() << "Fondo cargado correctamente";
    }

    // Posición inicial de Goku: esquina inferior izquierda del fondo
    int posXInicial = 0;
    int posYInicial = fondo.height() - 73;  // Altura del sprite

    goku = new Goku(posXInicial, posYInicial, ":/imagenes/spritegoku.png");

    // Establecer límites basados en el tamaño del fondo
    goku->establecerLimites(fondo.width(), fondo.height());

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
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
        // case Qt::Key_Up:
        // case Qt::Key_W:
        //     goku->moverArriba();
        //     break;
        case Qt::Key_Down:
        case Qt::Key_S:
            goku->moverAbajo();
            break;
        case Qt::Key_Space:
            goku->saltar();
            break;
        }
        update();
    }
    QWidget::keyPressEvent(event);
}

void AreaJuego::mousePressEvent(QMouseEvent* /*event*/)
{
    setFocus();
}

void AreaJuego::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);

    if (!fondo.isNull()) {
        int fondoX = (width() - fondo.width()) / 2;
        int fondoY = (height() - fondo.height()) / 2;

        painter.drawPixmap(fondoX, fondoY, fondo);
        painter.translate(fondoX, fondoY);
    } else {
        painter.fillRect(rect(), QColor(173, 216, 230));
    }

    if (goku) {
        goku->dibujar(painter);
    }
}
