#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMessageBox>
#include "proyectil.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , nivelActual(1)
{
    ui->setupUi(this);

    // Configurar escena y vista
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    view = new QGraphicsView(scene, this);
    view->setFixedSize(820, 620);
    setCentralWidget(view);

    // Goku
    goku = new Goku();
    goku->setPos(50, 500);
    scene->addItem(goku);

    // Label de vidas
    labelVidas = new QLabel(this);
    labelVidas->setText(QString("Vidas: %1").arg(goku->getVidas()));
    labelVidas->setStyleSheet("QLabel { color : white; font: bold 18px; background: rgba(0,0,0,100); }");
    labelVidas->setGeometry(10, 10, 120, 30);
    labelVidas->show();

    // Timer de proyectiles
    timerProyectiles = new QTimer(this);
    connect(timerProyectiles, &QTimer::timeout, this, [=](){
        qreal origenX = QRandomGenerator::global()->bounded(50, 750);
        qreal origenY = 0;
        qreal destinoX = QRandomGenerator::global()->bounded(50, 750);
        qreal destinoY = 580;

        Proyectil* p = new Proyectil(origenX, origenY, destinoX, destinoY);
        scene->addItem(p);
        proyectiles.append(p);
    });

    // Timer para colisiones
    QTimer* timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &MainWindow::verificarColisiones);
    timerColisiones->start(16);

    // Cargar el primer nivel
    cargarNivel(nivelActual);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::actualizarVidas()
{
    labelVidas->setText(QString("Vidas: %1").arg(goku->getVidas()));
}

void MainWindow::verificarColisiones()
{
    // Proyectiles
    for (int i = proyectiles.size() - 1; i >= 0; --i) {
        if (goku->collidesWithItem(proyectiles[i])) {
            goku->perderVida();
            actualizarVidas();
            goku->setPos(50, 500);
            proyectiles[i]->deleteLater();
            proyectiles.removeAt(i);

            if (goku->getVidas() == 0) {
                QMessageBox::information(this, "Game Over", "¡Perdiste! Reinicia el juego.");
                goku->reiniciarVidas();
                actualizarVidas();
                goku->setPos(50, 500);
            }
            break;
        }
    }

    // Esfera del dragón
    if (esfera && goku->collidesWithItem(esfera)) {
        // Eliminar la esfera de la escena
        scene->removeItem(esfera);
        delete esfera;
        esfera = nullptr;

        // Detener proyectiles del nivel 1
        timerProyectiles->stop();

        // Mostrar mensaje de transición
        QMessageBox::information(this, "¡Nivel Completado!", "¡Has conseguido la esfera del dragón!\n\n¡Prepárate para el siguiente nivel!");

        // Cambiar a nivel 2
        nivelActual = 2;
        cargarNivel(nivelActual);
    }
}

void MainWindow::cargarNivel(int nivel)
{
    limpiarNivel();

    // Cambiar fondo según el nivel
    if (nivel == 1) {
        scene->setBackgroundBrush(QPixmap(":/imagenes/escena1.png").scaled(820, 620));
    } else if (nivel == 2) {
        scene->setBackgroundBrush(QPixmap(":/imagenes/escena2.png").scaled(820, 620));
    }

    // Siempre agregamos a Goku
    goku->setPos(50, 500);
    scene->addItem(goku);

    // Plataformas y esfera según el nivel
    if (nivel == 1) {
        plataformas.append(new PlataformaFlotante(350, 400, 40, 2));
        plataformas.append(new PlataformaFlotante(450, 350, 30, 1.5));
        plataformas.append(new PlataformaFlotante(550, 300, 35, 1.8));
        plataformas.append(new PlataformaFlotante(650, 200, 25, 2.2));
        for (int i = 0; i < plataformas.size(); ++i)
            scene->addItem(plataformas[i]);

        esfera = new EsferaDragon(700, 100);
        scene->addItem(esfera);

        timerProyectiles->start(1800);
    }
    else if (nivel == 2) {
        // Ejemplo de obstáculos para el nivel 2 (puedes crear tus clases Roca/Elevacion)
        // plataformas.append(new Roca(200, 520));
        // plataformas.append(new Elevacion(400, 480));
        // for (int i = 0; i < plataformas.size(); ++i)
        //     scene->addItem(plataformas[i]);

        // Aquí puedes agregar a Yamcha y otros elementos del nivel 2

        // Si quieres proyectiles en el nivel 2, ajusta el timer:
        timerProyectiles->start(1200);
    }
}

void MainWindow::limpiarNivel()
{
    // Eliminar plataformas
    for (int i = 0; i < plataformas.size(); ++i) {
        scene->removeItem(plataformas[i]);
        delete plataformas[i];
    }
    plataformas.clear();

    // Eliminar esfera
    if (esfera) {
        scene->removeItem(esfera);
        delete esfera;
        esfera = nullptr;
    }

    // Eliminar proyectiles
    for (int i = 0; i < proyectiles.size(); ++i) {
        scene->removeItem(proyectiles[i]);
        delete proyectiles[i];
    }
    proyectiles.clear();

    // Si tienes enemigos, elimínalos aquí también
    // if (yamcha) { scene->removeItem(yamcha); delete yamcha; yamcha = nullptr; }
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
