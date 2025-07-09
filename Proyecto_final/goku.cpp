#include "goku.h"

Goku::Goku(float x, float y, QString archivoSprite)
    : ObjetoJuego(x, y, 50, 50) // Tamaño inicial
{
    cargarTextura(archivoSprite);
}

void Goku::actualizar(float tiempo)
{

}

void Goku::dibujar(QPainter& pintor)
{
    if (texturaObjeto && !texturaObjeto->isNull()) {
        pintor.drawPixmap(posicionX, posicionY, *texturaObjeto);
    }
}

void Goku::setColision(ObjetoJuego* otro)
{

}
