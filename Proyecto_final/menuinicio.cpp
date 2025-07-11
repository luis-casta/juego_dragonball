#include "menuinicio.h"
#include "ui_dialog.h"
#include <QUrl>

MenuInicio::MenuInicio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuInicioDialog)
{
    ui->setupUi(this);

    // Conectar botones
    connect(ui->btnJugar, &QPushButton::clicked, this, &MenuInicio::accept);
    connect(ui->btnSalir, &QPushButton::clicked, this, &MenuInicio::reject);

    // Configurar reproductor de audio
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    // Configurar volumen y conectar audio
    audioOutput->setVolume(0.8); // 80% volumen
    player->setAudioOutput(audioOutput);

    // Cargar y reproducir música
    player->setSource(QUrl("qrc:/imagenes/fondo.mp3"));
    player->setLoops(QMediaPlayer::Infinite);
    player->play();
}

MenuInicio::~MenuInicio()
{
    if (player) {
        player->stop();
    }
    delete ui;
}
