#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "areajuego.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void iniciarJuego();
    void salirJuego();
    void actualizarJuego();

private:
    Ui::MainWindow *ui;

    AreaJuego* areaJuego;
    QPushButton* botonIniciar;
    QPushButton* botonSalir;
    QLabel* labelPuntaje;
    QTimer* temporizador;
    int puntaje;
    bool juegoActivo;

    void crearInterfaz();
    void actualizarPuntaje();
};

#endif // MAINWINDOW_H
