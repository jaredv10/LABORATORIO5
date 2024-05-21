#include "tijeras.h"
#include <QPainter>
#include <QGraphicsScene>
#include "papel.h"

Tijeras::Tijeras() : imagen(":/images/tijera.png") {
    imagen = imagen.scaledToWidth(50, Qt::SmoothTransformation);
    // Posicionamiento inicial
    if (qrand() % 2 == 0) {
        setPos(0, qrand() % 600); // Izquierda
        velocidad = QPointF(30, 0);
    } else {
        setPos(800 - imagen.width(), qrand() % 600); // Derecha
        velocidad = QPointF(-30, 0);
    }
}

QRectF Tijeras::boundingRect() const {
    int margen = 5;
    return QRectF(-imagen.width() / 2 + margen, -imagen.height() / 2 + margen, imagen.width() - 2 * margen, imagen.height() - 2 * margen);
}

void Tijeras::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(-imagen.width() / 2, -imagen.height() / 2, imagen);
}

void Tijeras::advance(int phase) {
    if (!phase) return;

    QPointF newPos = pos() + velocidad;
    setPos(newPos);

    if (newPos.x() < 0 || newPos.x() > 800 - imagen.width()) {
        velocidad.rx() *= -1;
    }
}
