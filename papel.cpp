#include "papel.h"
#include <QPainter>
#include <QGraphicsScene>
#include "piedra.h"

Papel::Papel() : imagen(":/images/papel.png") {
    imagen = imagen.scaled(50, 50, Qt::KeepAspectRatio);
    // Posicionamiento inicial
    int esquina = qrand() % 4;
    switch (esquina) {
        case 0: setPos(0, 0); velocidad = QPointF(30, 30); break; // Esquina superior izquierda
        case 1: setPos(750, 0); velocidad = QPointF(-30, 30); break; // Esquina superior derecha
        case 2: setPos(0, 550); velocidad = QPointF(30, -30); break; // Esquina inferior izquierda
        case 3: setPos(750, 550); velocidad = QPointF(-30, -30); break; // Esquina inferior derecha
    }
}

QRectF Papel::boundingRect() const {
    int margen = 5;
    return QRectF(-imagen.width() / 2 + margen, -imagen.height() / 2 + margen, imagen.width() - 2 * margen, imagen.height() - 2 * margen);
}

void Papel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(-imagen.width() / 2, -imagen.height() / 2, imagen);
}

void Papel::advance(int phase) {
    if (!phase) return;

    QPointF newPos = pos() + velocidad;
    setPos(newPos);

    qreal sceneWidth = scene()->width();
    qreal sceneHeight = scene()->height();

    if (newPos.x() < 0 || newPos.x() > sceneWidth - imagen.width()) {
        velocidad.rx() *= -1;
    }
    if (newPos.y() < 0 || newPos.y() > sceneHeight - imagen.height()) {
        velocidad.ry() *= -1;
    }
}
