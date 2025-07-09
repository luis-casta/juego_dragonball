#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    puntaje = 0;
    juegoActivo = false;

    qDebug() << "Iniciando MainWindow";

    temporizador = new QTimer(this);
    temporizador->setInterval(16); // 60 FPS

    crearInterfaz();

    connect(botonIniciar, &QPushButton::clicked, this, &MainWindow::iniciarJuego);
    connect(botonSalir, &QPushButton::clicked, this, &MainWindow::salirJuego);
    connect(temporizador, &QTimer::timeout, this, &MainWindow::actualizarJuego);

    qDebug() << "MainWindow creado correctamente";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::crearInterfaz()
{
    QWidget* widgetCentral = new QWidget(this);
    setCentralWidget(widgetCentral);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout();

    areaJuego = new AreaJuego();
    areaJuego->setMinimumSize(800, 600);
    areaJuego->setStyleSheet("background-color: lightblue;");

    labelPuntaje = new QLabel("Puntaje: 0");
    labelPuntaje->setStyleSheet("font-size: 16px; font-weight: bold;");

    botonIniciar = new QPushButton("Iniciar Juego");
    botonSalir = new QPushButton("Salir");

    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addWidget(botonIniciar);
    layoutBotones->addWidget(botonSalir);

    layoutPrincipal->addWidget(areaJuego);
    layoutPrincipal->addWidget(labelPuntaje);
    layoutPrincipal->addLayout(layoutBotones);

    widgetCentral->setLayout(layoutPrincipal);

    setWindowTitle("Juego Dragon Ball");
    resize(850, 700);

    qDebug() << "Interfaz creada - AreaJuego:" << areaJuego->size();
}

void MainWindow::iniciarJuego()
{
    juegoActivo = true;
    puntaje = 0;
    actualizarPuntaje();
    temporizador->start();
    botonIniciar->setText("Reiniciar");
    qDebug() << "Juego iniciado";
}

void MainWindow::salirJuego()
{
    close();
}

void MainWindow::actualizarJuego()
{
    static int contador = 0;

    if (juegoActivo) {
        // Actualizar animación de Goku
        if (areaJuego && areaJuego->goku) {
            areaJuego->goku->actualizar(0.016f);  // 16ms por frame
        }

        contador++;

        // Solo suma puntaje cada 60 frames (1 segundo)
        if (contador >= 60) {
            puntaje += 1;
            actualizarPuntaje();
            contador = 0;
        }

        areaJuego->update();
    }
}

void MainWindow::actualizarPuntaje()
{
    labelPuntaje->setText(QString("Puntaje: %1").arg(puntaje));
}
