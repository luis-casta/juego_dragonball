#ifndef AREAJUEGO_H
#define AREAJUEGO_H

#include <QWidget>
#include <QPixmap>
#include "goku.h"

class AreaJuego : public QWidget
{
    Q_OBJECT

public:
    AreaJuego(QWidget* parent = nullptr);
    ~AreaJuego();

    Goku* goku;
    QPixmap fondo;

    void cambiarFondo(const QString& archivoFondo);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // AREAJUEGO_H
