#include "mainwindow.h"
#include <QKeyEvent>
#include <QRandomGenerator>
#include "proyectil.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Configurar escena y vista
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    view = new QGraphicsView(scene, this);
    view->setFixedSize(820, 620);
    setCentralWidget(view);

    // Configurar fondo
    QPixmap fondo(":/imagenes/escena1.png");
    if (!fondo.isNull())
        scene->setBackgroundBrush(fondo.scaled(820, 620));

    // Crear Goku
    goku = new Goku();
    goku->setPos(50, 500);
    scene->addItem(goku);

    // Crear label de vidas
    labelVidas = new QLabel(this);
    labelVidas->setText(QString("Vidas: %1").arg(goku->getVidas()));
    labelVidas->setStyleSheet("QLabel { color : white; font: bold 18px; background: rgba(0,0,0,100); }");
    labelVidas->setGeometry(10, 10, 120, 30);
    labelVidas->show();

    // Crear plataformas
    plataforma = new PlataformaFlotante(350, 400, 40, 2);
    scene->addItem(plataforma);

    PlataformaFlotante* plataforma2 = new PlataformaFlotante(450, 350, 30, 1.5);
    scene->addItem(plataforma2);

    PlataformaFlotante* plataforma3 = new PlataformaFlotante(550, 300, 35, 1.8);
    scene->addItem(plataforma3);

    PlataformaFlotante* plataforma4 = new PlataformaFlotante(650, 200, 25, 2.2);
    scene->addItem(plataforma4);

    // Crear esfera del dragón
    esfera = new EsferaDragon(700, 100);
    scene->addItem(esfera);

    // Configurar focus
    view->setFocus();

    // Timer para lanzar proyectiles
    timerProyectiles = new QTimer(this);
    connect(timerProyectiles, &QTimer::timeout, this, [=](){
        // Origen: X aleatorio en la parte superior de la escena
        qreal origenX = QRandomGenerator::global()->bounded(50, 750); // entre 50 y 750 px de ancho
        qreal origenY = 0; // parte superior

        // Destino: X aleatorio en la parte inferior de la escena
        qreal destinoX = QRandomGenerator::global()->bounded(50, 750); // entre 50 y 750 px de ancho
        qreal destinoY = 580; // cerca del suelo

        Proyectil* p = new Proyectil(origenX, origenY, destinoX, destinoY);
        scene->addItem(p);
        proyectiles.append(p);
    });
    timerProyectiles->start(1800); // Cada 1.8 segundos (puedes ajustar)
    // Timer para verificar colisiones
    QTimer* timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &MainWindow::verificarColisiones);
    timerColisiones->start(16); // 60 veces por segundo
}

MainWindow::~MainWindow() {}

void MainWindow::actualizarVidas()
{
    labelVidas->setText(QString("Vidas: %1").arg(goku->getVidas()));
}

void MainWindow::verificarColisiones()
{
    // Verificar colisiones con proyectiles
    for (int i = 0; i < proyectiles.size(); ++i) {
        if (goku->collidesWithItem(proyectiles[i])) {
            goku->perderVida();
            actualizarVidas();
            goku->setPos(50, 500);
            proyectiles[i]->deleteLater();
            proyectiles.removeAt(i);
            break;
        }
    }

    // Verificar colisión con esfera del dragón (ganar)
    if (goku->collidesWithItem(esfera)) {
        // Aquí puedes agregar lógica de victoria
        // Por ejemplo: mostrar mensaje "¡Ganaste!"
    }
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
