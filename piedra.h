#ifndef PIEDRA_H
#define PIEDRA_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Piedra : public QGraphicsPixmapItem
{
public:
    Piedra();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

private:
    QPixmap imagen;
    QPointF velocidad;
};

#endif // PIEDRA_H
