#ifndef PAPEL_H
#define PAPEL_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>

class Papel : public QGraphicsPixmapItem
{
public:
    Papel();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

private:
    QPixmap imagen;
    QPointF velocidad;
};

#endif // PAPEL_H
