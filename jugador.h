#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsRectItem>
#include <QObject>
#include <QKeyEvent>
#include <QPainter>

class Jugador : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    Jugador();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void objectDestroyed(const QString &tipoObjeto);

private:
    QPixmap imagen;
    void destruirObjetos();
};

#endif // JUGADOR_H
