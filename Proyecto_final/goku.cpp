#include "goku.h"
#include <QDebug>

Goku::Goku(float x, float y, QString archivoSprite)
    : ObjetoJuego(x, y, 61, 73)  // Tamaño del sprite
{
    cargarTextura(archivoSprite);

    anchoCuadro = 61;
    altoCuadro = 73;
    cuadrosPorFila = 11;
    cuadroActual = 0;
    contadorAnimacion = 0;
    velocidadAnimacion = 8;  // Velocidad de animación
    direccionActual = QUIETO;
    ultimaDireccion = ABAJO;

    limiteAncho = 800;
    limiteAlto = 600;

    moviendose = false;
    tiempoQuieto = 0;
    velocidadMovimiento = 4.0f;

    if (texturaObjeto && !texturaObjeto->isNull()) {
        qDebug() << "Sprite de Goku cargado correctamente";
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
    contadorAnimacion++;

    if (moviendose) {
        if (contadorAnimacion >= velocidadAnimacion) {
            cuadroActual++;
            if (cuadroActual >= 4) {  // Usar 4 cuadros por dirección
                cuadroActual = 0;
            }
            contadorAnimacion = 0;
        }
        tiempoQuieto = 0;
        ultimaDireccion = direccionActual;
    } else {
        tiempoQuieto++;
        if (tiempoQuieto < 60) {
            cuadroActual = 0;
        } else {
            if (contadorAnimacion >= 30) {
                cuadroActual = (cuadroActual == 0) ? 1 : 0;
                contadorAnimacion = 0;
            }
        }
        direccionActual = ultimaDireccion;
    }

    moviendose = false;
}

void Goku::dibujar(QPainter& pintor)
{
    if (texturaObjeto && !texturaObjeto->isNull()) {
        int cuadroFinal = obtenerCuadroParaDireccion(direccionActual, cuadroActual);

        int columna = cuadroFinal % cuadrosPorFila;
        int fila = cuadroFinal / cuadrosPorFila;

        int x = columna * anchoCuadro;
        int y = fila * altoCuadro;

        QPixmap cuadro = texturaObjeto->copy(x, y, anchoCuadro, altoCuadro);
        pintor.drawPixmap(posicionX, posicionY, cuadro);
    }
}

int Goku::obtenerCuadroParaDireccion(DireccionMovimiento direccion, int frame)
{
    switch (direccion) {
    case QUIETO:
    case ABAJO:
        return frame;  // Fila 0: cuadros 0-3
    case IZQUIERDA:
        return 11 + frame;  // Fila 1: cuadros 11-14
    case DERECHA:
        return 22 + frame;  // Fila 2: cuadros 22-25
    case ARRIBA:
        return 33 + frame;  // Fila 3: cuadros 33-36
    default:
        return 0;
    }
}

void Goku::cambiarDireccion(DireccionMovimiento nuevaDireccion)
{
    if (direccionActual != nuevaDireccion) {
        direccionActual = nuevaDireccion;
        cuadroActual = 0;
        contadorAnimacion = 0;
    }
    moviendose = true;
}

void Goku::moverIzquierda()
{
    float nuevaX = posicionX - velocidadMovimiento;
    if (nuevaX >= 0) {
        posicionX = nuevaX;
        cambiarDireccion(IZQUIERDA);
    }
}

void Goku::moverDerecha()
{
    float nuevaX = posicionX + velocidadMovimiento;
    if (nuevaX <= limiteAncho - anchoCuadro) {
        posicionX = nuevaX;
        cambiarDireccion(DERECHA);
    }
}

void Goku::moverArriba()
{
    float nuevaY = posicionY - velocidadMovimiento;
    if (nuevaY >= 0) {
        posicionY = nuevaY;
        cambiarDireccion(ARRIBA);
    }
}

void Goku::moverAbajo()
{
    float nuevaY = posicionY + velocidadMovimiento;
    if (nuevaY <= limiteAlto - altoCuadro) {
        posicionY = nuevaY;
        cambiarDireccion(ABAJO);
    }
}

void Goku::detenerMovimiento()
{
    moviendose = false;
}

void Goku::setColision(ObjetoJuego* /*otro*/)
{
    // Implementar lógica de colisión si es necesario
}
