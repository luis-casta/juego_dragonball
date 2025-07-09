#include "goku.h"

Goku::Goku(float x, float y, QString archivoSprite)
    : ObjetoJuego(x, y, 64, 64) // Tamaño de un cuadro del sprite
{
    cargarTextura(archivoSprite);
}

void Goku::actualizar(float /*tiempo*/)
{
    // Aquí puedes poner lógica extra si quieres
}

void Goku::dibujar(QPainter& pintor)
{
    if (texturaObjeto && !texturaObjeto->isNull()) {
        // Dibuja solo el primer cuadro (ajusta el tamaño si es necesario)
        QPixmap cuadro = texturaObjeto->copy(0, 0, 64, 64);
        pintor.drawPixmap(posicionX, posicionY, cuadro);
    }
}

void Goku::setColision(ObjetoJuego* /*otro*/)
{
    // Lógica de colisión (vacío por ahora)
}

void Goku::moverIzquierda()  { posicionX -= 5; }
void Goku::moverDerecha()    { posicionX += 5; }
void Goku::moverArriba()     { posicionY -= 5; }
void Goku::moverAbajo()      { posicionY += 5; }
