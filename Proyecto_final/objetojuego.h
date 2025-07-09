#ifndef OBJETOJUEGO_H
#define OBJETOJUEGO_H

#include <QPixmap>
#include <QRect>
#include <QPainter>

class ObjetoJuego
{
public:
    // Const
    ObjetoJuego();
    ObjetoJuego(float x, float y, float ancho, float alto);

    // Des
    virtual ~ObjetoJuego();

    // Métodos pa las clases hijas
    virtual void actualizar(float tiempo) = 0;
    virtual void dibujar(QPainter& pintor) = 0;
    virtual void setColision(ObjetoJuego* otro) = 0;

    bool estaActivo();
    void establecerActivo(bool activo);
    void setPosicion(float x, float y);
    QRect obtenerRectanguloColision();
    QPixmap obtenerPixMap();

    //  imagen del objeto
    void cargarTextura(QString archivo);

    // Obten valores
    float getPosicionX() { return posicionX; }
    float getPosicionY() { return posicionY; }
    float getVelocidadX() { return velocidadX; }
    float getVelocidadY() { return velocidadY; }
    float getAncho() { return anchoObjeto; }
    float getAlto() { return altoObjeto; }

    // Cambiar velocidad
    void setVelocidad(float vx, float vy);

protected:
    // Variables palas clases hijas
    float posicionX;
    float posicionY;
    float velocidadX;
    float velocidadY;
    float anchoObjeto;
    float altoObjeto;
    QPixmap* texturaObjeto;
    QRect* rectanguloColision;
    bool activo;
};

#endif // OBJETOJUEGO_H
