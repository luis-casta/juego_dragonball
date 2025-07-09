#include "goku.h"
#include <QDebug>

Goku::Goku(float x, float y, QString archivoSprite)
    : ObjetoJuego(x, y, 61, 73)  // Tamaño de cada cuadro
{
    cargarTextura(archivoSprite);

    anchoCuadro = 61;
    altoCuadro = 73;
    cuadrosPorFila = 11;  // Número de columnas en el sprite sheet
    cuadroActual = 0;
    contadorAnimacion = 0;
    velocidadAnimacion = 8;  // Controla la velocidad de cambio de cuadro
    direccionActual = QUIETO;

    if (texturaObjeto && !texturaObjeto->isNull()) {
        qDebug() << "Sprite cargado correctamente";
    } else {
        qDebug() << "Error al cargar sprite";
    }
}

void Goku::actualizar(float /*tiempo*/)
{
    contadorAnimacion++;
    if (contadorAnimacion >= velocidadAnimacion) {
        actualizarCuadro();
        contadorAnimacion = 0;
    }
}

void Goku::actualizarCuadro()
{
    if (direccionActual == QUIETO) {
        cuadroActual = 0;  // Quedarse en el primer cuadro cuando está quieto
    } else {
        cuadroActual++;
        if (cuadroActual >= 4) {  // Asumiendo 4 cuadros por animación
            cuadroActual = 0;
        }
    }
}

void Goku::dibujar(QPainter& pintor)
{
    if (!texturaObjeto || texturaObjeto->isNull()) return;

    int indiceCuadro = obtenerIndiceCuadro(direccionActual, cuadroActual);

    int fila = indiceCuadro / cuadrosPorFila;
    int columna = indiceCuadro % cuadrosPorFila;

    int x = columna * anchoCuadro;
    int y = fila * altoCuadro;

    QPixmap cuadro = texturaObjeto->copy(x, y, anchoCuadro, altoCuadro);
    pintor.drawPixmap(posicionX, posicionY, cuadro);
}

int Goku::obtenerIndiceCuadro(DireccionMovimiento direccion, int frame)
{
    switch (direccion) {
    case QUIETO:
        return 0;  // Primer cuadro de la fila 0
    case ABAJO:
        return frame;  // Fila 0, cuadros 0-3
    case IZQUIERDA:
        return 11 + frame;  // Fila 1, cuadros 11-14
    case DERECHA:
        return 22 + frame;  // Fila 2, cuadros 22-25
    case ARRIBA:
        return 33 + frame;  // Fila 3, cuadros 33-36
    default:
        return 0;
    }
}

void Goku::moverIzquierda()
{
    posicionX -= 4;  // Velocidad de movimiento
    cambiarDireccion(IZQUIERDA);
}

void Goku::moverDerecha()
{
    posicionX += 4;
    cambiarDireccion(DERECHA);
}

void Goku::detenerMovimiento()
{
    cambiarDireccion(QUIETO);
}

void Goku::cambiarDireccion(DireccionMovimiento nuevaDireccion)
{
    if (direccionActual != nuevaDireccion) {
        direccionActual = nuevaDireccion;
        cuadroActual = 0;  // Reiniciar animación al cambiar dirección
        contadorAnimacion = 0;
    }
}
