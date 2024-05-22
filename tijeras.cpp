#include "tijeras.h"
#include <QPixmap>
#include <QGraphicsScene>
Tijeras::Tijeras() {
    setPixmap(QPixmap(":/images/tijera.png").scaled(40, 40, Qt::KeepAspectRatio));
    if (qrand() % 2 == 0) {
        setPos(0, qrand() % 600); // Aparecer en el lado izquierdo
    } else {
        setPos(800 - boundingRect().width(), qrand() % 600);
    }
}

void Tijeras::advance(int phase) {
    if (!phase) return;
    setX(x() + 7);
    if (x() > 800) {
        scene()->removeItem(this);
        delete this;
    }
}

void Tijeras::mover() {

    setPos(x() + 10, y());
    



    if (pos().x() > scene()->width() - pixmap().width()) {

        setPos(scene()->width() - pixmap().width(), y());
    }
}
