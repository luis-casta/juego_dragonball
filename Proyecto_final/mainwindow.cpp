#include "ventanaprincipaljuego.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

VentanaPrincipalJuego::VentanaPrincipalJuego(QWidget *parent)
    : QMainWindow(parent)
{
    puntaje = 0;
    juegoActivo = false;

    // Crear el temporizador
    temporizador = new QTimer(this);
    temporizador->setInterval(16); // 60 FPS

    //  la interfaz
    crearInterfaz();

    //  señales
    connect(botonIniciar, &QPushButton::clicked, this, &VentanaPrincipalJuego::iniciarJuego);
    connect(botonSalir, &QPushButton::clicked, this, &VentanaPrincipalJuego::salirJuego);
    connect(temporizador, &QTimer::timeout, this, &VentanaPrincipalJuego::actualizarJuego);
}

void VentanaPrincipalJuego::crearInterfaz()
{
    // Widget central
    QWidget* widgetCentral = new QWidget(this);
    setCentralWidget(widgetCentral);

    // Layout principal
    QVBoxLayout* layoutPrincipal = new QVBoxLayout();

    // Área  el juego
    areaJuego = new QWidget();
    areaJuego->setMinimumSize(800, 600);
    areaJuego->setStyleSheet("background-color: lightblue;");

    // Label del puntaje
    labelPuntaje = new QLabel("Puntaje: 0");
    labelPuntaje->setStyleSheet("font-size: 16px; font-weight: bold;");

    // Botones
    botonIniciar = new QPushButton("Iniciar Juego");
    botonSalir = new QPushButton("Salir");

    // Layout para botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addWidget(botonIniciar);
    layoutBotones->addWidget(botonSalir);

    //  al layout principal
    layoutPrincipal->addWidget(areaJuego);
    layoutPrincipal->addWidget(labelPuntaje);
    layoutPrincipal->addLayout(layoutBotones);

    widgetCentral->setLayout(layoutPrincipal);

    // Configurar ventana
    setWindowTitle("Juego Dragon Ball");
    resize(850, 700);
}

void VentanaPrincipalJuego::iniciarJuego()
{
    juegoActivo = true;
    puntaje = 0;
    actualizarPuntaje();
    temporizador->start();
    botonIniciar->setText("Reiniciar");
}

void VentanaPrincipalJuego::salirJuego()
{
    close();
}

void VentanaPrincipalJuego::actualizarJuego()
{
    if (juegoActivo) {
        //  la lógica del juego
        //  el puntaje como ejemplo
        puntaje += 1;
        actualizarPuntaje();

        //  de juego se redibuje
        areaJuego->update();
    }
}

void VentanaPrincipalJuego::actualizarPuntaje()
{
    labelPuntaje->setText(QString("Puntaje: %1").arg(puntaje));
}
