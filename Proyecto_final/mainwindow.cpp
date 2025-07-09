#include "mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    QPixmap fondo(":/imagenes/escena1.png");
    scene->setSceneRect(0, 0, fondo.width(), fondo.height());
    scene->addPixmap(fondo);

    goku = new Goku();
    goku->setPos(0, fondo.height() - 79);  // Ajusta según altoCuadro
    scene->addItem(goku);

    setFocus();  // Para que MainWindow reciba eventos de teclado
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
    default:
        QMainWindow::keyReleaseEvent(event);
    }
}
