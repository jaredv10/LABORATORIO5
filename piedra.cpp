#include "piedra.h"
#include "tijeras.h"
#include <QPixmap>
#include <QGraphicsScene>

Piedra::Piedra() {
    setPixmap(QPixmap(":/images/piedra.png").scaled(40, 40, Qt::KeepAspectRatio));
    int side = qrand() % 2;
    if (side == 0) {
        setPos(qrand() % 760, 0);
        dy = 3;
    } else {
        setPos(qrand() % 760, 560);
        dy = -3;
    }
}

void Piedra::advance(int phase) {
    if (!phase) return;

    moveBy(0, dy);

    if (y() < 0 || y() > 560) {
        dy = -dy; // Invertir dirección vertical
    }

    // Verificar colisiones con tijeras
    QList<QGraphicsItem*> items = collidingItems();
    for (QGraphicsItem *item : items) {
        if (auto *tijeras = dynamic_cast<Tijeras*>(item)) {
            scene()->removeItem(tijeras);
            delete tijeras;
        }
    }
}

void Piedra::mover() {
    setPos(x(), y() + 10);
    if (pos().y() > scene()->height() - pixmap().height()) {
        setPos(x(), scene()->height() - pixmap().height());
    }
}
