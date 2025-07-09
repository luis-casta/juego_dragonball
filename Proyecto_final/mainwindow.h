#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "goku.h"
#include "plataforma.h"
#include "esferadragon.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    Goku* goku;
    PlataformaFlotante* plataforma;
    EsferaDragon* esfera;
};

#endif // MAINWINDOW_H
