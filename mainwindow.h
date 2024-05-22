#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "jugador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAgregarTijeras_clicked();
    void on_btnAgregarPiedra_clicked();
    void on_btnAgregarPapel_clicked();
    void on_btnIngresarJugador_clicked();
    void on_btnIniciar_clicked();
    void actualizarEscena();
    void generarObjetosAutomaticamente();
    void manejarDestruccionObjeto(const QString &tipoObjeto);

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

    void deshabilitarBotonesCreacionObjetos();
    void verificarColisiones();
    void actualizarTiempo();
    void actualizarContadores();
};

#endif // MAINWINDOW_H


#endif // MAINWINDOW_H

