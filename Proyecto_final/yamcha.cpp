#include "yamcha.h"
#include "proyectil.h"
#include <cmath>
#include <QGraphicsScene>
#include <QDebug>

Yamcha::Yamcha(qreal x, qreal y, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent),
    vida(5),
    velocidad(2.0),
    direccion(0),
    vx(0),
    vy(0),
    enElAire(false),
    frameActual(0),
    atacando(false),
    frameActualAtaque(0),
    contadorFrames(0)
{
    spriteSheet = QPixmap(":/imagenes/yamchaa.png");
    if (spriteSheet.isNull()) {
        qDebug() << "Error: No se pudo cargar el sprite yamchaa.png";
        return;
    }

    qDebug() << "Sprite cargado - Ancho total:" << spriteSheet.width()
             << "Alto total:" << spriteSheet.height()
             << "Esperado: 1088x1088";

    // Configurar las animaciones
    configurarAnimaciones();

    // Mostrar el frame inicial (quieto)
    mostrarFrame(animacionQuieto.fila, animacionQuieto.columnaInicio);
    setPos(x, y);

    // Hacer visible el item
    setVisible(true);
    setZValue(1);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Yamcha::actualizarMovimiento);
    timerMovimiento->start(30);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Yamcha::actualizarAnimacion);
    timerAnimacion->start(120);
}

void Yamcha::configurarAnimaciones()
{
    // Configurar las animaciones usando solo las primeras filas hasta la tercera columna

    // Animación quieto (primera fila, primera columna)
    animacionQuieto.fila = 0;
    animacionQuieto.columnaInicio = 0;
    animacionQuieto.columnaFin = 0; // Solo un frame para estar quieto

    // Animación caminar (primera fila, columnas 0-2)
    animacionCaminar.fila = 0;
    animacionCaminar.columnaInicio = 0;
    animacionCaminar.columnaFin = 2; // 3 frames de animación de caminar (columnas 0, 1, 2)

    // Animación ataque (segunda fila, columnas 0-2)
    animacionAtaque.fila = 1;
    animacionAtaque.columnaInicio = 0;
    animacionAtaque.columnaFin = 2; // 3 frames de animación de ataque

    // Animación salto (tercera fila, columnas 0-2)
    animacionSalto.fila = 2;
    animacionSalto.columnaInicio = 0;
    animacionSalto.columnaFin = 2; // 3 frames de animación de salto
}

void Yamcha::mostrarFrame(int fila, int columna)
{
    // Verificar límites
    if (fila < 0 || fila >= TOTAL_FILAS || columna < 0 || columna >= TOTAL_COLUMNAS) {
        qDebug() << "Frame fuera de límites - Fila:" << fila << "Columna:" << columna;
        return;
    }

    int xFrame = columna * ANCHO_FRAME;
    int yFrame = fila * ALTO_FRAME;

    // Verificar que el frame está dentro del sprite
    if (xFrame + ANCHO_FRAME <= spriteSheet.width() &&
        yFrame + ALTO_FRAME <= spriteSheet.height()) {

        QPixmap frame = spriteSheet.copy(xFrame, yFrame, ANCHO_FRAME, ALTO_FRAME);
        setPixmap(frame);

        qDebug() << "Mostrando frame - Fila:" << fila << "Columna:" << columna
                 << "X:" << xFrame << "Y:" << yFrame;
    } else {
        qDebug() << "Frame fuera del sprite - X:" << xFrame << "Y:" << yFrame;
    }
}

void Yamcha::moverIzquierda() {
    direccion = -1;
}

void Yamcha::moverDerecha() {
    direccion = 1;
}

void Yamcha::detener() {
    direccion = 0;
}

void Yamcha::actualizarMovimiento()
{
    if (direccion != 0) {
        vx += direccion * 0.5;
        if (vx > velocidad) vx = velocidad;
        if (vx < -velocidad) vx = -velocidad;
    } else {
        vx *= 0.8; // Fricción
    }

    setX(x() + vx);

    // Límites de pantalla
    if (x() < 0) setX(0);
    if (x() + ANCHO_FRAME > 800) setX(800 - ANCHO_FRAME);

    // Gravedad y suelo
    if (enElAire) {
        vy += 0.5; // Gravedad
        setY(y() + vy);
        if (y() >= 500) {
            setY(500);
            vy = 0;
            enElAire = false;
        }
    } else {
        // Mantener en el suelo
        if (y() != 500) {
            setY(500);
        }
    }
}

void Yamcha::actualizarAnimacion()
{
    contadorFrames++;

    if (atacando) {
        // Animación de ataque (fila 1, columnas 0-2)
        if (contadorFrames % 4 == 0) { // Cambiar frame cada 4 ciclos para ataque más lento
            frameActualAtaque++;
            if (frameActualAtaque > animacionAtaque.columnaFin) {
                frameActualAtaque = animacionAtaque.columnaInicio;
                atacando = false; // Terminar ataque
            }
        }
        mostrarFrame(animacionAtaque.fila, frameActualAtaque);

    } else if (enElAire) {
        // Animación de salto (fila 2, columnas 0-2)
        int frameSalto = animacionSalto.columnaInicio + (contadorFrames / 6) %
                                                            (animacionSalto.columnaFin - animacionSalto.columnaInicio + 1);
        mostrarFrame(animacionSalto.fila, frameSalto);

    } else if (direccion != 0) {
        // Animación de caminar (fila 0, columnas 0-2)
        if (contadorFrames % 3 == 0) { // Cambiar frame cada 3 ciclos
            frameActual++;
            if (frameActual > animacionCaminar.columnaFin) {
                frameActual = animacionCaminar.columnaInicio;
            }
        }
        mostrarFrame(animacionCaminar.fila, frameActual);

    } else {
        // Animación quieto (fila 0, columna 0)
        mostrarFrame(animacionQuieto.fila, animacionQuieto.columnaInicio);
        frameActual = animacionCaminar.columnaInicio; // Reset para próximo movimiento
    }
}

void Yamcha::saltar()
{
    if (!enElAire) {
        vy = -10;
        enElAire = true;
    }
}

void Yamcha::iniciarAtaque()
{
    atacando = true;
    frameActualAtaque = animacionAtaque.columnaInicio;
}

void Yamcha::atacarAGoku(QGraphicsItem* goku)
{
    if (!scene() || !goku) return;

    qreal dx = goku->x() - this->x();
    qreal dy = goku->y() - this->y();
    qreal distancia = sqrt(dx*dx + dy*dy);

    if (distancia > 400) return;

    iniciarAtaque();

    // Crear proyectil
    qreal velocidadProyectil = 6.0;
    qreal vxProyectil = velocidadProyectil * (dx / distancia);
    qreal vyProyectil = velocidadProyectil * (dy / distancia) - 2.0;

    Proyectil* proyectil = new Proyectil(this->x() + 30, this->y() + 20, vxProyectil, vyProyectil, DeYamcha);
    scene()->addItem(proyectil);
}

void Yamcha::recibirDanio(int cantidad)
{
    vida -= cantidad;
    if (vida <= 0) {
        emit yamchaDerrotado();
    }
}

int Yamcha::getVida() const {
    return vida;
}

void Yamcha::setVida(int nuevaVida) {
    vida = nuevaVida;
}
