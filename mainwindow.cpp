#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tijeras.h"
#include "piedra.h"
#include "papel.h"
#include "jugador.h"
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , contadorTijeras(0)
    , contadorPiedra(0)
    , contadorPapel(0)
    , puntajeJugador(0)
    , tiempoRestante(300)
    , modoJugador(false)
{
    ui->setupUi(this);
    escena = new QGraphicsScene(0, 0, 800, 600, this);
    ui->graphicsView->setScene(escena);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEscena);
    timerGeneracion = new QTimer(this);
    connect(timerGeneracion, &QTimer::timeout, this, &MainWindow::generarObjetosAutomaticamente);

    QVBoxLayout *layoutVertical = new QVBoxLayout(ui->centralwidget);
    ui->centralwidget->setLayout(layoutVertical);

    layoutVertical->addWidget(ui->graphicsView);
    layoutVertical->addWidget(ui->lblTiempo);
    layoutVertical->addWidget(ui->btnIniciar);
    layoutVertical->addWidget(ui->btnAgregarTijeras);
    layoutVertical->addWidget(ui->btnAgregarPiedra);
    layoutVertical->addWidget(ui->btnAgregarPapel);
    layoutVertical->addWidget(ui->btnIngresarJugador);
    layoutVertical->addWidget(ui->lblContadorTijeras);
    layoutVertical->addWidget(ui->lblContadorPiedra);
    layoutVertical->addWidget(ui->lblContadorPapel);
    layoutVertical->addWidget(ui->lblPuntajeJugador);



    jugador = new Jugador();
    escena->addItem(jugador);
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    jugador->setFocus();
    connect(jugador, &Jugador::objectDestroyed, this, &MainWindow::manejarDestruccionObjeto);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnAgregarTijeras_clicked() {
    if (contadorTijeras < 5) {

        bool colision;
        Tijeras *tijeras;
        do {
            colision = false;
            tijeras = new Tijeras();
            QList<QGraphicsItem*> items = escena->items(tijeras->boundingRect());
            for (QGraphicsItem *item : items) {
                if (dynamic_cast<Tijeras*>(item)) {
                    colision = true;
                    delete tijeras;
                    break;
                }
            }
        } while (colision);
        escena->addItem(tijeras);
        contadorTijeras++;
        actualizarContadores();
    }
}

void MainWindow::on_btnAgregarPiedra_clicked() {
    if (contadorPiedra < 5) {

        bool colision;
        Piedra *piedra;
        do {
            colision = false;
            piedra = new Piedra();
            QList<QGraphicsItem*> items = escena->items(piedra->boundingRect());
            for (QGraphicsItem *item : items) {
                if (dynamic_cast<Piedra*>(item)) {
                    colision = true;
                    delete piedra;
                    break;
                }
            }
        } while (colision);
        escena->addItem(piedra);
        contadorPiedra++;
        actualizarContadores();
    }
}

void MainWindow::on_btnAgregarPapel_clicked() {
    if (contadorPapel < 5) {
        Papel *papel = new Papel();
        escena->addItem(papel);
        contadorPapel++;
        actualizarContadores();
    }
}

void MainWindow::actualizarEscena() {
    escena->advance();
    verificarColisiones();
    actualizarTiempo();
}


void MainWindow::deshabilitarBotonesCreacionObjetos() {
    ui->btnAgregarTijeras->setDisabled(true);
    ui->btnAgregarPiedra->setDisabled(true);
    ui->btnAgregarPapel->setDisabled(true);
}

void MainWindow::on_btnIngresarJugador_clicked() {
    modoJugador = true;
    tiempoRestante = 300;
    jugador->setPos(375, 275);
    timer->start(1000);
    deshabilitarBotonesCreacionObjetos();

    QMessageBox::information(this, "Mensaje", "Para mover al jugador utilice las teclas de direccion. Y para dispararle a los objetos con la tecla space .");
}

void MainWindow::on_btnIniciar_clicked() {
    timer->start(1000);
    timerGeneracion->start(10000);

    QMessageBox::information(this, "Mensaje", "Bienvenido al juego Papel, Tijera y Piedra,Disfrutelo\
PD: tienes 5:00 minutos para jugar.");
}



void MainWindow::generarObjetosAutomaticamente() {
    if (contadorTijeras < 5) {
        Tijeras *tijeras = new Tijeras();
        escena->addItem(tijeras);
        contadorTijeras++;
    }
    if (contadorPiedra < 5) {
        Piedra *piedra = new Piedra();
        escena->addItem(piedra);
        contadorPiedra++;
    }
    if (contadorPapel < 5) {
        Papel *papel = new Papel();
        escena->addItem(papel);
        contadorPapel++;
    }
    actualizarContadores();
}

void MainWindow::manejarDestruccionObjeto(const QString &tipoObjeto) {
    if (tipoObjeto == "Tijeras") {
        contadorTijeras--;
        puntajeJugador++;
    } else if (tipoObjeto == "Piedra") {
        contadorPiedra--;
        puntajeJugador++;
    } else if (tipoObjeto == "Papel") {
        contadorPapel--;
        puntajeJugador++;
    }
    actualizarContadores();
}

void MainWindow::verificarColisiones() {
    QList<QGraphicsItem *> items = escena->items();
    QSet<QGraphicsItem *> itemsParaEliminar;

    for (QGraphicsItem *item1 : items) {
        for (QGraphicsItem *item2 : items) {
            if (item1 == item2) continue;
            if (item1->collidesWithItem(item2)) {
                if ((dynamic_cast<Tijeras*>(item1) && dynamic_cast<Papel*>(item2)) ||
                    (dynamic_cast<Tijeras*>(item2) && dynamic_cast<Papel*>(item1))) {
                    itemsParaEliminar.insert(item1);
                    itemsParaEliminar.insert(item2);
                    puntajeJugador += 2;
                } else if ((dynamic_cast<Piedra*>(item1) && dynamic_cast<Tijeras*>(item2)) ||
                           (dynamic_cast<Piedra*>(item2) && dynamic_cast<Tijeras*>(item1))) {
                    itemsParaEliminar.insert(item1);
                    itemsParaEliminar.insert(item2);
                    puntajeJugador += 2;
                } else if ((dynamic_cast<Papel*>(item1) && dynamic_cast<Piedra*>(item2)) ||
                           (dynamic_cast<Papel*>(item2) && dynamic_cast<Piedra*>(item1))) {
                    itemsParaEliminar.insert(item1);
                    itemsParaEliminar.insert(item2);
                    puntajeJugador += 2;
                }
            }
        }
    }

    for (QGraphicsItem *item : itemsParaEliminar) {
        escena->removeItem(item);
        if (dynamic_cast<Tijeras*>(item)) {
            contadorTijeras--;
        } else if (dynamic_cast<Piedra*>(item)) {
            contadorPiedra--;
        } else if (dynamic_cast<Papel*>(item)) {
            contadorPapel--;
        }
        delete item;
    }

    actualizarContadores();
}

void MainWindow::actualizarTiempo() {
    tiempoRestante--;
    ui->lblTiempo->setText("Tiempo restante: " + QString::number(tiempoRestante));
    ui->lblPuntajeJugador->setText("Puntaje: " + QString::number(puntajeJugador));
    if (tiempoRestante <= 0) {
        timer->stop();
        timerGeneracion->stop();
        QMessageBox::information(this, "Tiempo agotado", "El tiempo se ha agotado. Puntaje: " + QString::number(puntajeJugador));
    }
}


void MainWindow::actualizarContadores() {
    ui->lblContadorTijeras->setText("Tijeras: " + QString::number(contadorTijeras));
    ui->lblContadorPiedra->setText("Piedras: " + QString::number(contadorPiedra));
    ui->lblContadorPapel->setText("Papel: " + QString::number(contadorPapel));
}

