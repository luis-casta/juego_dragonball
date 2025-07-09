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

    // Posición inicial de Goku: en el suelo del fondo
    int posXInicial = (fondo.width() / 2) - 30;  // Centrado horizontalmente, ajusta 30 según ancho de Goku
    int posYInicial = fondo.height() - 73;       // Altura del fondo menos altura de Goku (73)

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

        // Trasladar el origen para que Goku se dibuje relativo al fondo
        painter.translate(fondoX, fondoY);
    } else {
        painter.fillRect(rect(), QColor(173, 216, 230));
    }

    if (goku) {
        goku->dibujar(painter);
    }
}
