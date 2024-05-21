#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "jugador.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAgregarTijeras_clicked();
    void on_btnAgregarPiedra_clicked();
    void on_btnAgregarPapel_clicked();
    void on_btnIngresarJugador_clicked();
    void on_btnIniciar_clicked();
    void actualizarEscena();
    void generarObjetosAutomaticamente();
    void actualizarContadores();
    void actualizarTiempo();
    void manejarDestruccionObjeto(const QString &tipoObjeto);
    void objectDestroyedHandler(const QString &tipoObjeto);
        void verificarColisiones();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;
    QTimer *timer;
    QTimer *timerGeneracion;
    Jugador *jugador;
    int contadorTijeras;
    int contadorPiedra;
    int contadorPapel;
    int puntajeJugador;
    int tiempoRestante;
    bool modoJugador;

protected:
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // MAINWINDOW_H

