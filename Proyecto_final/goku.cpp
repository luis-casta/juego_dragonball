#include "goku.h"
#include <QDebug>

Goku::Goku(float x, float y, QString archivoSprite)
    : ObjetoJuego(x, y, 61, 73)  // Nuevo tamaño
{
    cargarTextura(archivoSprite);

    // Configuración para el nuevo sprite
    anchoCuadro = 61;      // 677 / 11 = 61.5 ≈ 61
    altoCuadro = 73;       // 369 / 5 = 73.8 ≈ 73
    cuadrosPorFila = 11;   // 11 columnas
    cuadroActual = 0;
    contadorAnimacion = 0;
    velocidadAnimacion = 10;
    direccionActual = QUIETO;

    limiteAncho = 800;
    limiteAlto = 600;

    if (texturaObjeto && !texturaObjeto->isNull()) {
        qDebug() << "Sprite de Goku cargado correctamente";
        qDebug() << "Tamaño:" << texturaObjeto->width() << "x" << texturaObjeto->height();
    } else {
        qDebug() << "ERROR: No se pudo cargar el sprite de Goku";
    }
}

void Goku::establecerLimites(int ancho, int alto)
{
    limiteAncho = ancho;
    limiteAlto = alto;
}

void Goku::actualizar(float /*tiempo*/)
{
    if (direccionActual != QUIETO) {
        contadorAnimacion++;

        if (contadorAnimacion >= velocidadAnimacion) {
            cuadroActual++;

            // Usar 6 cuadros de animación por dirección
            if (cuadroActual >= 6) {
                cuadroActual = 0;
            }

            contadorAnimacion = 0;
        }
    } else {
        cuadroActual = 0;
    }

    direccionActual = QUIETO;
}

void Goku::dibujar(QPainter& pintor)
{
    if (texturaObjeto && !texturaObjeto->isNull()) {
        int cuadroFinal = obtenerCuadroParaDireccion(direccionActual, cuadroActual);

        int columna = cuadroFinal % cuadrosPorFila;
        int fila = cuadroFinal / cuadrosPorFila;

        int x = columna * anchoCuadro;
        int y = fila * altoCuadro;

        // Extraer y dibujar el cuadro (ya tiene transparencia)
        QPixmap cuadro = texturaObjeto->copy(x, y, anchoCuadro, altoCuadro);
        pintor.drawPixmap(posicionX, posicionY, cuadro);
    }
}

int Goku::obtenerCuadroParaDireccion(DireccionMovimiento direccion, int frame)
{
    // Mapeo basado en las filas del nuevo sprite
    switch (direccion) {
    case QUIETO:
        return 0;  // Primera pose
    case ABAJO:
        return frame;  // Fila 0: cuadros 0-10
    case IZQUIERDA:
        return 11 + frame;  // Fila 1: cuadros 11-21
    case DERECHA:
        return 22 + frame;  // Fila 2: cuadros 22-32
    case ARRIBA:
        return 33 + frame;  // Fila 3: cuadros 33-43
    default:
        return 0;
    }
}

void Goku::cambiarDireccion(DireccionMovimiento nuevaDireccion)
{
    direccionActual = nuevaDireccion;
}

void Goku::moverIzquierda()
{
    float nuevaX = posicionX - 5;
    if (nuevaX >= 0) {
        posicionX = nuevaX;
        cambiarDireccion(IZQUIERDA);
    }
}

void Goku::moverDerecha()
{
    float nuevaX = posicionX + 5;
    if (nuevaX <= limiteAncho - anchoCuadro) {
        posicionX = nuevaX;
        cambiarDireccion(DERECHA);
    }
}

void Goku::moverArriba()
{
    float nuevaY = posicionY - 5;
    if (nuevaY >= 0) {
        posicionY = nuevaY;
        cambiarDireccion(ARRIBA);
    }
}

void Goku::moverAbajo()
{
    float nuevaY = posicionY + 5;
    if (nuevaY <= limiteAlto - altoCuadro) {
        posicionY = nuevaY;
        cambiarDireccion(ABAJO);
    }
}

void Goku::setColision(ObjetoJuego* /*otro*/)
{
    // Lógica de colisión
}
