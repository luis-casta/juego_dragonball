#include "mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->scale(1.5, 1.5);
    setCentralWidget(view);

    QPixmap fondo(":/imagenes/escena1.png");
    scene->setSceneRect(0, 0, fondo.width(), fondo.height());
    scene->addPixmap(fondo);

    goku = new Goku();
    goku->setPos(0, fondo.height() - 79);  // Ajusta segun cuadro
    scene->addItem(goku);

    setFocus();  // eventos de teclado
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()) {
    case Qt::Key_Left:
        goku->moverIzquierda();
        break;
    case Qt::Key_Right:
        goku->moverDerecha();
        break;
    case Qt::Key_Space:
        goku->saltar();
        break;
    case Qt::Key_Down:
        goku->agacharse();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
        goku->detenerMovimiento();
        break;
    case Qt::Key_Down:
        goku->levantarse();
        break;
    default:
        QMainWindow::keyReleaseEvent(event);
    }
}
