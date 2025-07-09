#include "mainwindow.h"
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    QPixmap fondo(":/imagenes/escena1.png");
    scene->setSceneRect(0, 0, fondo.width(), fondo.height());
    scene->addPixmap(fondo);

    // Crear y agregar Goku
    goku = new Goku();
    goku->setPos(0, fondo.height() - 73);  // Posición inicial en la base del fondo
    scene->addItem(goku);

    // Darle foco para que reciba eventos de teclado
    goku->setFocus();
}

MainWindow::~MainWindow()
{
}
