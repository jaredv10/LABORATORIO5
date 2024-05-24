#include "papel.h"
#include "tijeras.h"
#include <QPixmap>
#include <QGraphicsScene>

Papel::Papel() {
    setPixmap(QPixmap(":/images/papel.png").scaled(40, 40, Qt::KeepAspectRatio));
    int corner = qrand() % 4;
    switch (corner) {
        case 0:
            setPos(0, 0);
            break;
        case 1:
            setPos(760, 0);
            break;
        case 2:
            setPos(0, 560);
            break;
    case 3:
        setPos(760, 560);
        break;
}
dx = (corner == 1 || corner == 3) ? -3 : 3;
dy = (corner == 2 || corner == 3) ? -3 : 3;
}

void Papel::advance(int phase) {
if (!phase) return;

moveBy(dx, dy);

if (x() < 0 || x() > 760) {
    dx = -dx; // Invertir dirección horizontal
}
if (y() < 0 || y() > 560) {
    dy = -dy; // Invertir dirección vertical
}
}

void Papel::mover() {
setPos(x() + 10, y() - 10);
if (pos().y() < 0 || pos().x() > scene()->width()) {
    scene()->removeItem(this);
    delete this;
}
}
