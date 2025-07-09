#include "mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    view = new QGraphicsView(scene, this);
    view->setFixedSize(820, 620);
    setCentralWidget(view);

    QPixmap fondo(":/imagenes/escena1.png");
    if (!fondo.isNull())
        scene->setBackgroundBrush(fondo.scaled(820, 620));

    goku = new Goku();
    goku->setPos(50, 500);
    scene->addItem(goku);

    labelVidas = new QLabel(this);
    labelVidas->setText(QString("Vidas: %1").arg(goku->getVidas()));
    labelVidas->setStyleSheet("QLabel { color : white; font: bold 18px; background: rgba(0,0,0,100); }");
    labelVidas->setGeometry(10, 10, 120, 30);
    labelVidas->show();
    // Plataforma flotante
    plataforma = new PlataformaFlotante(350, 400, 40, 2);
    scene->addItem(plataforma);

    PlataformaFlotante* plataforma2 = new PlataformaFlotante(450, 350, 30, 1.5);
    scene->addItem(plataforma2);

    PlataformaFlotante* plataforma3 = new PlataformaFlotante(550, 300, 35, 1.8);
    scene->addItem(plataforma3);

    PlataformaFlotante* plataforma4 = new PlataformaFlotante(650, 200, 25, 2.2);
    scene->addItem(plataforma4);

    // Esfera del dragón
    esfera = new EsferaDragon(700, 100);
    scene->addItem(esfera);
    view->setFocus();
}

MainWindow::~MainWindow() {}
void MainWindow::actualizarVidas()
{
    labelVidas->setText(QString("Vidas: %1").arg(goku->getVidas()));
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()) {
    case Qt::Key_A:
        goku->moverIzquierda();
        break;
    case Qt::Key_D:
        goku->moverDerecha();
        break;
    case Qt::Key_Space:
        goku->saltar();
        break;
    case Qt::Key_S:
        goku->agacharse();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key()) {
    case Qt::Key_A:
    case Qt::Key_D:
        goku->detenerMovimiento();
        break;
    case Qt::Key_S:
        goku->levantarse();
        break;
    default:
        QMainWindow::keyReleaseEvent(event);
    }
}
