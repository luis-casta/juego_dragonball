#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QAbstractButton>
#include "proyectil.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), esferasRestantes(0), esfera1(nullptr)
    , esfera2(nullptr), nivelActual(1)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);//escen ppal

    view = new QGraphicsView(scene, this);
    view->setFixedSize(820, 620);//vista
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
    timerMovimientoYamcha = nullptr;
    esfera = nullptr;

    //  primer nivel
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
    // Colisiones con proyectiles
    for (int i = proyectiles.size() - 1; i >= 0; --i) {
        if (goku->collidesWithItem(proyectiles[i])) {
            goku->perderVida();
            actualizarVidas();
            goku->setPos(50, 500);

            scene->removeItem(proyectiles[i]);
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

    // Colisión con Yamcha
    if (yamcha && goku->collidesWithItem(yamcha)) {
        if (goku->x() < yamcha->x()) {
            goku->setX(yamcha->x() - goku->boundingRect().width());
        } else {
            goku->setX(yamcha->x() + yamcha->boundingRect().width());
        }
    }

    // Colisión con esfera del nivel 1
    if (esfera && goku->collidesWithItem(esfera)) {
        scene->removeItem(esfera);
        delete esfera;
        esfera = nullptr;

        timerProyectiles->stop();
        QMessageBox::information(this, "¡Nivel Completado!", "¡Has conseguido la esfera del dragón!\n\n¡Prepárate para el siguiente nivel!");

        nivelActual = 2;
        cargarNivel(nivelActual);
        return; // Evitar seguir ejecutando
    }

    // Colisión con las dos esferas restantes tras vencer a Yamcha (nivel 2)
    if (esferasRestantes > 0) {
        if (esfera1 && goku->collidesWithItem(esfera1)) {
            scene->removeItem(esfera1);
            delete esfera1;
            esfera1 = nullptr;
            esferasRestantes--;
        }
        if (esfera2 && goku->collidesWithItem(esfera2)) {
            scene->removeItem(esfera2);
            delete esfera2;
            esfera2 = nullptr;
            esferasRestantes--;
        }

        if (esferasRestantes == 0) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("¡Felicidades!");
            msgBox.setText("¡Felicidades! Conseguíste las esferas del dragón. Pide un deseo. Se cumplirá pronto");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

            if (auto btnYes = msgBox.button(QMessageBox::Yes))
                btnYes->setText("Volver a jugar");
            if (auto btnNo = msgBox.button(QMessageBox::No))
                btnNo->setText("Salir");

            int ret = msgBox.exec();

            if (ret == QMessageBox::Yes) {
                // Reiniciar juego
                nivelActual = 1;
                goku->reiniciarVidas();
                actualizarVidas();
                cargarNivel(nivelActual);
            } else {
                // Salir del programa
                qApp->quit();
            }
            return; // Evitar seguir ejecutando
        }
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

    // Eliminar esferas restantes nivel 2
    if (esfera1) {
        scene->removeItem(esfera1);
        delete esfera1;
        esfera1 = nullptr;
    }
    if (esfera2) {
        scene->removeItem(esfera2);
        delete esfera2;
        esfera2 = nullptr;
    }
    esferasRestantes = 0;

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

    // Detener y eliminar el timer de movimiento de Yamcha
    if (timerMovimientoYamcha) {
        timerMovimientoYamcha->stop();
        delete timerMovimientoYamcha;
        timerMovimientoYamcha = nullptr;
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
        plataformas.append(new PlataformaFlotante(100, 400, 35, 2,false,true));//1
        plataformas.append(new PlataformaFlotante(300, 300, 15, 1.5,true,true));//2
        plataformas.append(new PlataformaFlotante(500, 250, 25, 1.8,true,false));// ambos ejes
        plataformas.append(new PlataformaFlotante(650, 200, 10, 2.2,true,true));//4

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
        view->setFixedSize(800, 600);

        // Eliminar Yamcha anterior si existe
        if (yamcha) {
            disconnect(yamcha, &Yamcha::yamchaDerrotado, nullptr, nullptr);
            scene->removeItem(yamcha);
            delete yamcha;
            yamcha = nullptr;
        }

        // Crear nuevo Yamcha
        yamcha = new Yamcha(650, 500);
        scene->addItem(yamcha);

        // Conectar señal de muerte a slot
        connect(yamcha, &Yamcha::yamchaDerrotado, this, &MainWindow::onYamchaDerrotado);

        // movimiento automático a Yamcha
        timerMovimientoYamcha = new QTimer(this);
        connect(timerMovimientoYamcha, &QTimer::timeout, this, [=](){
            if (yamcha && goku) {
                // Hacer que Yamcha se mueva hacia Goku
                qreal distanciaX = goku->x() - yamcha->x();

                if (abs(distanciaX) > 50) { // Solo moverse si está lejos
                    if (distanciaX > 0) {
                        yamcha->moverDerecha();
                    } else {
                        yamcha->moverIzquierda();
                    }
                } else {
                    yamcha->detener();}}});

        timerMovimientoYamcha->start(100); // Actualizar cada 100ms

        // Timer para ataques de Yamcha
        if (timerAtaqueYamcha) {
            timerAtaqueYamcha->stop();
            delete timerAtaqueYamcha;
            timerAtaqueYamcha = nullptr;
        }
        timerAtaqueYamcha = new QTimer(this);
        connect(timerAtaqueYamcha, &QTimer::timeout, this, [=](){
            if (yamcha && goku) {
                yamcha->atacarAGoku(goku);

                // los proyectiles de Yamcha a la lista
                QList<QGraphicsItem*> items = scene->items();
                for (QGraphicsItem* item : std::as_const(items)) {
                    Proyectil* proyectil = dynamic_cast<Proyectil*>(item);
                    if (proyectil && proyectil->getTipo() == DeYamcha) {
                        // Solo agregar si no está ya en la lista
                        if (!proyectiles.contains(proyectil)) {
                            proyectiles.append(proyectil);}}}}
        });
        timerAtaqueYamcha->start(2000);

        timerProyectiles->start(1200);
    }

    //  Goku
    goku->setPos(50, 500);
    scene->addItem(goku);
}

void MainWindow::onYamchaDerrotado()
{

    if (timerAtaqueYamcha) {
        timerAtaqueYamcha->stop();
        delete timerAtaqueYamcha;
        timerAtaqueYamcha = nullptr;
    }

    // para timer de proyectiles que caen del cielo
    if (timerProyectiles->isActive()) {
        timerProyectiles->stop();
    }

    // Elimina Yamcha de la escena
    if (yamcha) {
        scene->removeItem(yamcha);
        delete yamcha;
        yamcha = nullptr;
    }

    // Elimina todos los proyectiles
    for (int i = proyectiles.size() - 1; i >= 0; --i) {
        scene->removeItem(proyectiles[i]);
        delete proyectiles[i];
        proyectiles.removeAt(i);
    }

    QMessageBox::information(this, "¡Yamcha Derrotado!", "Has derrotado a Yamcha. Ahora recoge las dos esferas restantes.");

    // Agregar las dos esferas restantes para el nivel 2
    esfera1 = new EsferaDragon(600, 450);
    esfera2 = new EsferaDragon(650, 400);
    scene->addItem(esfera1);
    scene->addItem(esfera2);

    esferasRestantes = 2;
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
    case Qt::Key_W:
        if (yamcha) {
            goku->atacar(yamcha);
        }
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
