#include "jugador.h"
#include "tijeras.h"
#include "piedra.h"
#include "papel.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QPainter>

Jugador::Jugador() {
    imagen = QPixmap(":/images/jugador.png").scaled(50, 50, Qt::KeepAspectRatio);
    setRect(0, 0, 50, 50);
}

QRectF Jugador::boundingRect() const {
    return QRectF(0, 0, 50, 50);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0, 0, imagen);
}

void Jugador::advance(int phase) {
    if (!phase) return;
}

void Jugador::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
            setX(x() - 10); // Mueve el jugador a la izquierda
            break;
        case Qt::Key_Right:
            setX(x() + 10); // Mueve el jugador a la derecha
            break;
        case Qt::Key_Up:
            setY(y() - 10); // Mueve el jugador hacia arriba
            break;
        case Qt::Key_Down:
            setY(y() + 10); // Mueve el jugador hacia abajo
            break;
        case Qt::Key_Space:
            destruirObjetos(); // Destruye objetos cuando se presiona Espacio
            break;
        default:
            break;
    }
}

void Jugador::destruirObjetos() {
    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        if (auto *tijeras = dynamic_cast<Tijeras*>(item)) {
            emit objectDestroyed("Tijeras");
            scene()->removeItem(tijeras);
            delete tijeras;
        } else if (auto *piedra = dynamic_cast<Piedra*>(item)) {
            emit objectDestroyed("Piedra");
            scene()->removeItem(piedra);
            delete piedra;
        } else if (auto *papel = dynamic_cast<Papel*>(item)) {
            emit objectDestroyed("Papel");
            scene()->removeItem(papel);
            delete papel;
        }
    }
}
