#ifndef PAPEL_H
#define PAPEL_H

#include <QGraphicsPixmapItem>
#include <QTimer>
class Papel : public QGraphicsPixmapItem {
public:
    Papel();
    void advance(int phase) override;

private:
    int dx;
    int dy;
    void mover();

};

#endif // PAPEL_H
