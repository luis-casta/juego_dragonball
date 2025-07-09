#include "objetojuego.h"

ObjetoJuego::ObjetoJuego()
{
    posicionX = 0;
    posicionY = 0;
    velocidadX = 0;
    velocidadY = 0;
    anchoObjeto = 50;
    altoObjeto = 50;
    texturaObjeto = new QPixmap();
    rectanguloColision = new QRect(0, 0, 50, 50);
    activo = true;
}

ObjetoJuego::ObjetoJuego(float x, float y, float ancho, float alto)
{
    posicionX = x;
    posicionY = y;
    velocidadX = 0;
    velocidadY = 0;
    anchoObjeto = ancho;
    altoObjeto = alto;
    texturaObjeto = new QPixmap();
    rectanguloColision = new QRect(x, y, ancho, alto);
    activo = true;
}

ObjetoJuego::~ObjetoJuego()
{
    if (texturaObjeto) {
        delete texturaObjeto;
    }
    if (rectanguloColision) {
        delete rectanguloColision;
    }
}

bool ObjetoJuego::estaActivo()
{
    return activo;
}

void ObjetoJuego::establecerActivo(bool nuevoActivo)
{
    activo = nuevoActivo;
}

void ObjetoJuego::setPosicion(float x, float y)
{
    posicionX = x;
    posicionY = y;

    // Actualiza el rectángulo de colisión
    rectanguloColision->setX(x);
    rectanguloColision->setY(y);
}

QRect ObjetoJuego::obtenerRectanguloColision()
{
    return *rectanguloColision;
}

QPixmap ObjetoJuego::obtenerPixMap()
{
    return *texturaObjeto;
}

void ObjetoJuego::cargarTextura(QString archivo)
{
    texturaObjeto->load(archivo);

    // Si la imagen se cargo correctamente, ajust el tamaño
    if (!texturaObjeto->isNull()) {
        anchoObjeto = texturaObjeto->width();
        altoObjeto = texturaObjeto->height();
        rectanguloColision->setWidth(anchoObjeto);
        rectanguloColision->setHeight(altoObjeto);
    }
}

void ObjetoJuego::setVelocidad(float vx, float vy)
{
    velocidadX = vx;
    velocidadY = vy;
}
