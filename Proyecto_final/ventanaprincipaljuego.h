#ifndef VENTANAPRINCIPALJUEGO_H
#define VENTANAPRINCIPALJUEGO_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class VentanaPrincipalJuego : public QMainWindow
{
    Q_OBJECT

public:
    VentanaPrincipalJuego(QWidget *parent = nullptr);

private slots:
    void iniciarJuego();
    void salirJuego();
    void actualizarJuego();

private:
    QTimer* temporizador;
    QPushButton* botonIniciar;
    QPushButton* botonSalir;
    QLabel* labelPuntaje;
    QWidget* areaJuego;

    int puntaje;
    bool juegoActivo;

    void crearInterfaz();
    void actualizarPuntaje();
};

#endif // VENTANAPRINCIPALJUEGO_H
