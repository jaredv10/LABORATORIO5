#include "piedra.h"
#include <QPixmap>
#include <QGraphicsScene>

Piedra::Piedra() {
    setPixmap(QPixmap(":/images/piedra.png").scaled(40, 40, Qt::KeepAspectRatio));
    // Generar en el borde superior o inferior
    int side = qrand() % 2;
    if (side == 0) {
        setPos(qrand() % 770, 0);
    } else {
        setPos(qrand() % 770, 570);
    }
    dy = (side == 0) ? 3 : -3;
}

void Piedra::advance(int phase) {
    if (!phase) return;
    moveBy(0, dy);
    if (y() < 0 || y() > 570) {
        scene()->removeItem(this);
        delete this;
    }
}
void Piedra::mover() {

    setPos(x(), y() + 10);


    if (pos().y() > scene()->height() - pixmap().height()) {

        setPos(x(), scene()->height() - pixmap().height());
    }
}
