#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QLabel>
#include <QList>
#include <QKeyEvent>
#include "goku.h"
#include "plataforma.h"
#include "esferadragon.h"
#include "proyectil.h"
#include "yamcha.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private slots:
    void verificarColisiones();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QLabel* labelVidas;

    // Objetos del juego
    Goku* goku;
    QList<PlataformaFlotante*> plataformas;
    EsferaDragon* esfera;
    Yamcha* yamcha = nullptr;
    QTimer* timerAtaqueYamcha = nullptr;
    QTimer* timerMovimientoYamcha = nullptr; // NUEVO: Timer para movimiento automático

    // Proyectiles y timer
    QList<Proyectil*> proyectiles;
    QTimer* timerProyectiles;

    // Niveles
    int nivelActual;

    // Funciones auxiliares
    void actualizarVidas();
    void iniciarSiguienteNivel();
    void cargarNivel(int nivel);
    void limpiarNivel();
};

#endif // MAINWINDOW_H
