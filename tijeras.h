#ifndef TIJERAS_H
#define TIJERAS_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>

class Tijeras : public QGraphicsPixmapItem
{
public:
    Tijeras();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

private:
    QPixmap imagen;
    QPointF velocidad;
};

#endif // TIJERAS_H
