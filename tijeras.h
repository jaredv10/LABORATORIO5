#ifndef TIJERAS_H
#define TIJERAS_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
class Tijeras : public QGraphicsPixmapItem {
public:
    Tijeras();
    void advance(int phase) override;

private:
    int dx;
    void mover();

};

#endif // TIJERAS_H
