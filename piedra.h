#ifndef PIEDRA_H
#define PIEDRA_H

#include <QGraphicsPixmapItem>
#include <QTimer>
class Piedra : public QGraphicsPixmapItem {
public:
    Piedra();
    void advance(int phase) override;

private:
    int dy;
    void mover();

};

#endif // PIEDRA_H
