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
    scene->setSceneRect(0, 0, 820, 620);

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

    // Inicialización de punteros
    yamcha = nullptr;
    timerAtaqueYamcha = nullptr;
    esfera = nullptr;

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

    // Desconectar y eliminar Yamcha
    if (yamcha) {
        disconnect(yamcha, &Yamcha::yamchaDerrotado, nullptr, nullptr);
        scene->removeItem(yamcha);
        delete yamcha;
        yamcha = nullptr;
    }

    // Detener y eliminar el timer de ataque de Yamcha
    if (timerAtaqueYamcha) {
        timerAtaqueYamcha->stop();
        delete timerAtaqueYamcha;
        timerAtaqueYamcha = nullptr;
    }

    // Detener timer de proyectiles para evitar conflictos
    if (timerProyectiles->isActive()) {
        timerProyectiles->stop();
    }
}

void MainWindow::cargarNivel(int nivel)
{
    limpiarNivel();

    if (nivel == 1) {
        scene->setSceneRect(0, 0, 800, 600);
        scene->setBackgroundBrush(QPixmap(":/imagenes/escena1.png").scaled(800, 600));
        view->setFixedSize(820, 620);

        // Plataformas del nivel 1
        plataformas.append(new PlataformaFlotante(350, 400, 40, 2));
        plataformas.append(new PlataformaFlotante(450, 350, 30, 1.5));
        plataformas.append(new PlataformaFlotante(550, 300, 35, 1.8));
        plataformas.append(new PlataformaFlotante(650, 200, 25, 2.2));

        for (int i = 0; i < plataformas.size(); ++i)
            scene->addItem(plataformas[i]);

        // Esfera del dragón nivel 1
        esfera = new EsferaDragon(700, 100);
        scene->addItem(esfera);

        timerProyectiles->start(1800);
    }
    else if (nivel == 2) {
        scene->setSceneRect(0, 0, 800, 600);
        scene->setBackgroundBrush(QPixmap(":/imagenes/escena2.png").scaled(800, 600));
        view->setFixedSize(820, 620);

        // Eliminar Yamcha anterior si existe
        if (yamcha) {
            disconnect(yamcha, &Yamcha::yamchaDerrotado, nullptr, nullptr);
            scene->removeItem(yamcha);
            delete yamcha;
            yamcha = nullptr;
        }

        yamcha = new Yamcha(500, 345);
        scene->addItem(yamcha);

        connect(yamcha, &Yamcha::yamchaDerrotado, this, [=](){
            QMessageBox::information(this, "¡Yamcha Derrotado!",
                                     "¡Has derrotado a Yamcha!\n\n"
                                     "Ahora debes recoger las dos esferas del dragón.");

            EsferaDragon* esfera1 = new EsferaDragon(600, 450);
            EsferaDragon* esfera2 = new EsferaDragon(650, 400);
            scene->addItem(esfera1);
            scene->addItem(esfera2);

            // Agrega lógica para esferas nivel 2 si tienes
        });

        // Timer para ataques automáticos de Yamcha
        if (timerAtaqueYamcha) {
            timerAtaqueYamcha->stop();
            delete timerAtaqueYamcha;
            timerAtaqueYamcha = nullptr;
        }
        timerAtaqueYamcha = new QTimer(this);
        connect(timerAtaqueYamcha, &QTimer::timeout, this, [=](){
            if (yamcha && goku)
                yamcha->atacarAGoku(goku);
        });
        timerAtaqueYamcha->start(2000);

        timerProyectiles->start(1200);
    }

    // Siempre agregamos a Goku
    goku->setPos(50, 500);
    scene->addItem(goku);
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
