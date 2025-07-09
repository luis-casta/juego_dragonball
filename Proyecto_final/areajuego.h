#ifndef AREAJUEGO_H
#define AREAJUEGO_H

#include <QWidget>
#include <QPixmap>
#include <QKeyEvent>
#include "goku.h"

class AreaJuego : public QWidget
{
    Q_OBJECT

public:
    explicit AreaJuego(QWidget* parent = nullptr);
    ~AreaJuego();

    void actualizar(float deltaTiempo);

    Goku* goku;

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QPixmap fondo;
};

#endif // AREAJUEGO_H
