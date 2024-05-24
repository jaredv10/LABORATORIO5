#include "tijeras.h"
#include "papel.h"
#include <QPixmap>
#include <QGraphicsScene>

Tijeras::Tijeras() {
    setPixmap(QPixmap(":/images/tijera.png").scaled(40, 40, Qt::KeepAspectRatio));
    if (qrand() % 2 == 0) {
        setPos(0, qrand() % 600); // Aparecer en el lado izquierdo
        dx = 7;
    } else {
        setPos(800 - boundingRect().width(), qrand() % 600);
        dx = -7;
    }
}

void Tijeras::advance(int phase) {
    if (!phase) return;

    moveBy(dx, 0);

    if (x() < 0 || x() > 760) {
        dx = -dx; // Invertir dirección horizontal
    }

    // Verificar colisiones con papel
    QList<QGraphicsItem*> items = collidingItems();
    for (QGraphicsItem *item : items) {
        if (auto *papel = dynamic_cast<Papel*>(item)) {
            scene()->removeItem(papel);
            delete papel;
        }
    }
}

void Tijeras::mover() {
    setPos(x() + 10, y());
    if (pos().x() > scene()->width() - pixmap().width()) {
        setPos(scene()->width() - pixmap().width(), y());
    }
}
