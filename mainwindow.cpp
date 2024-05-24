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

    timer = new QTimer(this);  // Temporizador para los objetos
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEscena);

    timerGeneracion = new QTimer(this); // Temporizador para la generación de objetos
    connect(timerGeneracion, &QTimer::timeout, this, &MainWindow::generarObjetosAutomaticamente);

    timerTiempo = new QTimer(this); // Temporizador para el tiempo restante
    connect(timerTiempo, &QTimer::timeout, this, &MainWindow::actualizarTiempo);

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
        bool colision;
        Papel *papel;
        do {
            colision = false;
            papel = new Papel();
            QList<QGraphicsItem*> items = escena->items(papel->boundingRect());
            for (QGraphicsItem *item : items) {
                if (dynamic_cast<Papel*>(item)) {
                    colision = true;
                    delete papel;
                    break;
                }
            }
        } while (colision);
        escena->addItem(papel);
        contadorPapel++;
        actualizarContadores();
    }
}

void MainWindow::on_btnIngresarJugador_clicked() {
    modoJugador = true;
    jugador->setFocus();

    QMessageBox::information(this, "Mensaje", "Para mover al jugador utilice las teclas de direccion. Y para dispararle a los objetos con la tecla space .");
}

void MainWindow::on_btnIniciar_clicked() {
    timer->start(1000 / 40); // Actualizar objetos a 60 FPS
    timerGeneracion->start(10000);
    timerTiempo->start(1000);

    QMessageBox::information(this, "Mensaje", "Bienvenido al juego Papel, Tijera y Piedra,Disfrutelo\
    PD: tienes 5:00 minutos para jugar.");
}

void MainWindow::actualizarEscena() {
    escena->advance();
    verificarColisiones();
}

void MainWindow::verificarColisiones() {
    QList<QGraphicsItem*> items = escena->items();
    for (QGraphicsItem *item : items) {
        if (auto *tijeras = dynamic_cast<Tijeras*>(item)) {
            QList<QGraphicsItem*> colisiones = tijeras->collidingItems();
            for (QGraphicsItem *colision : colisiones) {
                if (auto *papel = dynamic_cast<Papel*>(colision)) {
                    escena->removeItem(papel);
                    delete papel;
                }
            }
        } else if (auto *piedra = dynamic_cast<Piedra*>(item)) {
            QList<QGraphicsItem*> colisiones = piedra->collidingItems();
            for (QGraphicsItem *colision : colisiones) {
                if (auto *tijeras = dynamic_cast<Tijeras*>(colision)) {
                    escena->removeItem(tijeras);
                    delete tijeras;
                }
            }
        } else if (auto *papel = dynamic_cast<Papel*>(item)) {
            QList<QGraphicsItem*> colisiones = papel->collidingItems();
            for (QGraphicsItem *colision : colisiones) {
                if (auto *piedra = dynamic_cast<Piedra*>(colision)) {
                    escena->removeItem(piedra);
                    delete piedra;
                }
            }
        }
    }
}

void MainWindow::actualizarContadores() {
    ui->lblContadorTijeras->setText("Tijeras: " + QString::number(contadorTijeras));
    ui->lblContadorPiedra->setText("Piedras: " + QString::number(contadorPiedra));
    ui->lblContadorPapel->setText("Papel: " + QString::number(contadorPapel));
}

void MainWindow::actualizarTiempo() {
    if (tiempoRestante > 0) {
        tiempoRestante--;
        ui->lblTiempo->setText("Tiempo restante: " + QString::number(tiempoRestante));
    } else {
        timer->stop();
        timerGeneracion->stop();
        timerTiempo->stop();
        QMessageBox::information(this, "Tiempo finalizado", "El tiempo se ha agotado.");
    }
}

void MainWindow::generarObjetosAutomaticamente() {
    int tipoObjeto = qrand() % 3;

    switch (tipoObjeto) {
        case 0:
            on_btnAgregarTijeras_clicked();
            break;
        case 1:
            on_btnAgregarPiedra_clicked();
            break;
        case 2:
            on_btnAgregarPapel_clicked();
            break;
    }
}

void MainWindow::deshabilitarBotonesCreacionObjetos() {
    ui->btnAgregarTijeras->setEnabled(false);
    ui->btnAgregarPiedra->setEnabled(false);
    ui->btnAgregarPapel->setEnabled(false);
}

void MainWindow::manejarDestruccionObjeto(const QString &tipoObjeto) {
    if (tipoObjeto == "Tijeras") {
        contadorTijeras--;
    } else if (tipoObjeto == "Piedra") {
        contadorPiedra--;
    } else if (tipoObjeto == "Papel") {
        contadorPapel--;
    }

    puntajeJugador++;
    ui->lblPuntajeJugador->setText("Puntaje: " + QString::number(puntajeJugador));
    actualizarContadores();
}
