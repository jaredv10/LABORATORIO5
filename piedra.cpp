#include "piedra.h"
#include <QPainter>
#include <QGraphicsScene>
#include "papel.h"

Piedra::Piedra() : imagen(":/images/piedra.png") {
    imagen = imagen.scaledToWidth(50, Qt::SmoothTransformation);
    // Posicionamiento inicial
    if (qrand() % 2 == 0) {
        setPos(qrand() % 800, 0); // Arriba
        velocidad = QPointF(0, 30);
    } else {
        setPos(qrand() % 800, 600 - imagen.height()); // Abajo
        velocidad = QPointF(0, -30);
    }
}

QRectF Piedra::boundingRect() const {
    int margen = 5;
    return QRectF(-imagen.width() / 2 + margen, -imagen.height() / 2 + margen, imagen.width() - 2 * margen, imagen.height() - 2 * margen);
}

void Piedra::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(-imagen.width() / 2, -imagen.height() / 2, imagen);
}

void Piedra::advance(int phase) {
    if (!phase) return;

    QPointF newPos = pos() + velocidad;
    setPos(newPos);

    if (newPos.y() < 0 || newPos.y() > 600 - imagen.height()) {
        velocidad.ry() *= -1;
    }
}
