#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class AreaJuego;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void actualizarJuego();

private:
    AreaJuego* areaJuego;
    QTimer* temporizador;
};

#endif // MAINWINDOW_H
