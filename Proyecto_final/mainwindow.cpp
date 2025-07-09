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

    botonIniciar = new QPushButton("Iniciar Juego");
    botonSalir = new QPushButton("Salir");

    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addWidget(botonIniciar);
    layoutBotones->addWidget(botonSalir);

    layoutPrincipal->addWidget(areaJuego);
    layoutPrincipal->addLayout(layoutBotones);

    widgetCentral->setLayout(layoutPrincipal);

    setWindowTitle("Juego Dragon Ball");
    resize(850, 700);

    qDebug() << "Interfaz creada - AreaJuego:" << areaJuego->size();
}

void MainWindow::iniciarJuego()
{
    juegoActivo = true;
    temporizador->start();
    botonIniciar->setText("Reiniciar");

    areaJuego->setFocus();

    qDebug() << "Juego iniciado - Foco establecido en AreaJuego";
}

void MainWindow::salirJuego()
{
    close();
}

void MainWindow::actualizarJuego()
{
    if (juegoActivo) {
        if (areaJuego && areaJuego->goku) {
            areaJuego->goku->actualizar(0.016f);  // 16ms por frame
        }
        areaJuego->update();
    }
}
