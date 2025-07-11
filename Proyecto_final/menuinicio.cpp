#include "menuinicio.h"
#include "ui_dialog.h"

#include <QUrl>

MenuInicio::MenuInicio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuInicioDialog),
    player(new QMediaPlayer(this)),
    audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);

    // Conectar botones del UI
    connect(ui->btnJugar, &QPushButton::clicked, this, &MenuInicio::accept);
    connect(ui->btnSalir, &QPushButton::clicked, this, &MenuInicio::reject);

    // Configurar y reproducir música de fondo
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/imagenes/fondo.mp3"));
    audioOutput->setVolume(30);  // Volumen entre 0.0 y 1.0
    player->play();
}

MenuInicio::~MenuInicio()
{
    delete ui;
}
