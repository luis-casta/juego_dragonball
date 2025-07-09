#include "goku.h"
#include <QDebug>

Goku::Goku(float x, float y, QString archivoSprite)
    : ObjetoJuego(x, y, 61, 73)
{
    cargarTextura(archivoSprite);

    anchoCuadro = 61;
    altoCuadro = 73;
    cuadrosPorFila = 11;
    cuadroActual = 0;
    contadorAnimacion = 0;
    velocidadAnimacion = 8;
    direccionActual = QUIETO;
    ultimaDireccion = ABAJO;

    limiteAncho = 800;
    limiteAlto = 600;

    moviendose = false;
    tiempoQuieto = 0;
    velocidadMovimiento = 4.0f;

    estadoSalto = SIN_SALTO;
    alturaSaltoMax = 100.0f;
    velocidadSalto = 6.0f;
    posicionYInicial = y;

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

void Goku::actualizar(float tiempo)
{
    contadorAnimacion++;

    manejarSalto(tiempo);

    if (moviendose) {
        if (contadorAnimacion >= velocidadAnimacion) {
            cuadroActual++;
            if (cuadroActual >= 4) {
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

void Goku::manejarSalto(float /*tiempo*/)
{
    if (estadoSalto == SUBIENDO) {
        posicionY -= velocidadSalto;
        if (posicionY <= posicionYInicial - alturaSaltoMax) {
            estadoSalto = BAJANDO;
        }
    } else if (estadoSalto == BAJANDO) {
        posicionY += velocidadSalto;
        if (posicionY >= posicionYInicial) {
            posicionY = posicionYInicial;
            estadoSalto = SIN_SALTO;
        }
    }
}

void Goku::dibujar(QPainter& pintor)
{
    if (texturaObjeto && !texturaObjeto->isNull()) {
        int indiceCuadro = obtenerIndiceCuadro(direccionActual, cuadroActual);

        int fila = indiceCuadro / cuadrosPorFila;
        int columna = indiceCuadro % cuadrosPorFila;

        int x = columna * anchoCuadro;
        int y = fila * altoCuadro;

        QPixmap cuadro = texturaObjeto->copy(x, y, anchoCuadro, altoCuadro);
        pintor.drawPixmap(posicionX, posicionY, cuadro);
    }
}

int Goku::obtenerIndiceCuadro(DireccionMovimiento direccion, int frame)
{
    switch (direccion) {
    case QUIETO:
    case ABAJO:
        return frame;
    case IZQUIERDA:
        return 11 + frame;
    case DERECHA:
        return 22 + frame;
    case ARRIBA:
        return 33 + frame;
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
    moviendose = (nuevaDireccion != QUIETO);
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

void Goku::detenerMovimiento()
{
    cambiarDireccion(QUIETO);
}

void Goku::saltar()
{
    if (estadoSalto == SIN_SALTO) {
        estadoSalto = SUBIENDO;
    }
}

void Goku::setColision(ObjetoJuego* /*otro*/)
{

}
