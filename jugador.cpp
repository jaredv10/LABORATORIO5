#include "jugador.h"
#include <QGraphicsScene>
#include "tijeras.h"
#include "piedra.h"
#include "papel.h"

#include <QKeyEvent>

Jugador::Jugador() {
    setRect(0, 0, 50, 50);
}

void Jugador::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        setPos(x(), y() - 10);
        break;
    case Qt::Key_A:
        setPos(x() - 10, y());
        break;
    case Qt::Key_S:
        setPos(x(), y() + 10);
        break;
    case Qt::Key_D:
        setPos(x() + 10, y());
        break;
    case Qt::Key_Space:
        emit objectDestroyed("jugador");
        break;
    }
}
