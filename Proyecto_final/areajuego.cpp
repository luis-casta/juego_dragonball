#include "areajuego.h"
#include <QPainter>
#include <QDebug>
#include <QColor>

AreaJuego::AreaJuego(QWidget* parent)
    : QWidget(parent)
{
    if (!fondo.load(":/imagenes/escena1.png")) {
        qDebug() << "ERROR: No se pudo cargar el fondo";
    } else {
        qDebug() << "Fondo cargado correctamente";
    }

    int posXInicial = 0;
    int posYInicial = fondo.height() - 73;  // Altura sprite Goku

    goku = new Goku(posXInicial, posYInicial, ":/imagenes/spritegoku.png");
    goku->establecerLimites(fondo.width(), fondo.height());

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

AreaJuego::~AreaJuego()
{
    delete goku;
}

void AreaJuego::actualizar(float /*deltaTiempo*/)
{
    if (goku) {
        goku->actualizar(0.016f);
    }
    update();
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

void AreaJuego::keyPressEvent(QKeyEvent* event)
{
    if (!goku) return;

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        goku->moverIzquierda();
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        goku->moverDerecha();
        break;
    case Qt::Key_Space:
        goku->saltar();
        break;
    }

    update();
    QWidget::keyPressEvent(event);
}

void AreaJuego::keyReleaseEvent(QKeyEvent* event)
{
    if (!goku) return;

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
    case Qt::Key_Right:
    case Qt::Key_D:
        goku->detenerMovimiento();
        break;
    }

    update();
    QWidget::keyReleaseEvent(event);
}

void AreaJuego::mousePressEvent(QMouseEvent* /*event*/)
{
    setFocus();
}
