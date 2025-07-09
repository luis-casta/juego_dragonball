#include "mainwindow.h"
#include "areajuego.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    areaJuego = new AreaJuego(this);
    setCentralWidget(areaJuego);

    temporizador = new QTimer(this);
    temporizador->setInterval(16);  // 60 FPS aprox.

    connect(temporizador, &QTimer::timeout, this, &MainWindow::actualizarJuego);

    temporizador->start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::actualizarJuego()
{
    if (areaJuego) {
        areaJuego->actualizar(0.016f);
    }
}
