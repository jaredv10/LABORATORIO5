#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QKeyEvent>

class Jugador : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    Jugador();
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void objectDestroyed(const QString &tipoObjeto);
};

#endif // JUGADOR_H
