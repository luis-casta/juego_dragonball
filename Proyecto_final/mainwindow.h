#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QLabel>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Forward declarations
class Goku;
class PlataformaFlotante;
class EsferaDragon;
class Proyectil;

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

    // Elementos gráficos
    QGraphicsScene* scene;
    QGraphicsView* view;
    QLabel* labelVidas;

    // Objetos del juego
    Goku* goku;
    PlataformaFlotante* plataforma;
    PlataformaFlotante* plataforma2;
    PlataformaFlotante* plataforma3;
    PlataformaFlotante* plataforma4;
    EsferaDragon* esfera;

    // Proyectiles y timer
    QList<Proyectil*> proyectiles;
    QTimer* timerProyectiles;

    // Función auxiliar
    void actualizarVidas();
};

#endif // MAINWINDOW_H
