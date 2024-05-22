#include "papel.h"
#include <QPixmap>
#include <QGraphicsScene>

Papel::Papel() {
    setPixmap(QPixmap(":/images/papel.png").scaled(40, 40, Qt::KeepAspectRatio));
    // Generar en una de las esquinas
    int corner = qrand() % 4;
    switch (corner) {
        case 0:
            setPos(0, 0);
            break;
        case 1:
            setPos(770, 0);
            break;
        case 2:
            setPos(0, 570);
            break;
        case 3:
            setPos(770, 570);
            break;
    }
    dx = (corner == 1 || corner == 3) ? -3 : 3;
    dy = (corner == 2 || corner == 3) ? -3 : 3;
}

void Papel::advance(int phase) {
    if (!phase) return;
    moveBy(dx, dy);
    if (x() < 0 || x() > 770 || y() < 0 || y() > 570) {
        scene()->removeItem(this);
        delete this;
    }
}
void Papel::mover() {

    setPos(x() + 10, y() - 10);


    if (pos().y() < 0 || pos().x() > scene()->width()) {

        scene()->removeItem(this);
        delete this;
    }
}
