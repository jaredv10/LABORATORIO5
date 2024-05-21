#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tijeras.h"
#include "piedra.h"
#include "papel.h"
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QVBoxLayout>

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
    escena = new QGraphicsScene(0, 0, 800, 600,this);
    ui->graphicsView->setScene(escena);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEscena);
    timerGeneracion = new QTimer(this);
    connect(timerGeneracion, &QTimer::timeout, this, &MainWindow::generarObjetosAutomaticamente);

    QVBoxLayout *layoutVertical = new QVBoxLayout(ui->centralwidget);
    ui->centralwidget->setLayout(layoutVertical);

    layoutVertical->addWidget(ui->graphicsView);
    layoutVertical->addWidget(ui->lblTiempo);
    layoutVertical->addWidget(ui->btnAgregarTijeras);
    layoutVertical->addWidget(ui->btnAgregarPiedra);
    layoutVertical->addWidget(ui->btnAgregarPapel);
    layoutVertical->addWidget(ui->btnIngresarJugador);
    layoutVertical->addWidget(ui->lblContadorTijeras);
    layoutVertical->addWidget(ui->lblContadorPiedra);
    layoutVertical->addWidget(ui->lblContadorPapel);
    layoutVertical->addWidget(ui->lblPuntajeJugador);

    connect(ui->btnIniciar, &QPushButton::clicked, this, &MainWindow::on_btnIniciar_clicked);

    // Crear el jugador y conectar la señal objectDestroyed
    jugador = new Jugador();
    escena->addItem(jugador);
    connect(jugador, &Jugador::objectDestroyed, this, &MainWindow::objectDestroyedHandler);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnAgregarTijeras_clicked() {
    if (contadorTijeras < 5) {
        Tijeras *tijeras = new Tijeras();
        escena->addItem(tijeras);
        contadorTijeras++;
        actualizarContadores();
    }
}

void MainWindow::on_btnAgregarPiedra_clicked() {
    if (contadorPiedra < 5) {
        Piedra *piedra = new Piedra();
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

void MainWindow::on_btnIngresarJugador_clicked() {
    modoJugador = true;
    tiempoRestante = 300;
    jugador->setPos(375, 275); // Posición inicial del jugador
    timer->start(1000); // El timer se actualiza cada segundo
    timerGeneracion->start(10000); // Generar objetos cada 10 segundos
}

void MainWindow::on_btnIniciar_clicked() {
    timer->start(1000); // El timer se actualiza cada segundo
}

void MainWindow::actualizarEscena() {
    escena->advance();
    verificarColisiones();
    actualizarTiempo();
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

void MainWindow::verificarColisiones() {
    QList<QGraphicsItem*> objetos = escena->items();

    for (int i = 0; i < objetos.size(); ++i) {
        QGraphicsItem *objeto = objetos.at(i);
        QList<QGraphicsItem*> colisiones = objeto->collidingItems();

        for (QGraphicsItem *colision : colisiones) {
            if (Tijeras *tijeras = dynamic_cast<Tijeras*>(objeto)) {
                if (Papel *papel = dynamic_cast<Papel*>(colision)) {
                    escena->removeItem(papel);
                    delete papel;
                    contadorPapel--;
                    contadorTijeras++;
                    actualizarContadores();
                    break;
                }
            } else if (Piedra *piedra = dynamic_cast<Piedra*>(objeto)) {
                if (Tijeras *tijeras = dynamic_cast<Tijeras*>(colision)) {
                    escena->removeItem(tijeras);
                    delete tijeras;
                    contadorTijeras--;
                    contadorPiedra++;
                    actualizarContadores();
                    break;
                } else if (Papel *papel = dynamic_cast<Papel*>(colision)) {
                    escena->removeItem(piedra);
                    delete piedra;
                    contadorPiedra--;
                    contadorPapel++;
                    actualizarContadores();
                    break;
                }
            } else if (Papel *papel = dynamic_cast<Papel*>(objeto)) {
                if (Piedra *piedra = dynamic_cast<Piedra*>(colision)) {
                    escena->removeItem(piedra);
                    delete piedra;
                    contadorPiedra--;
                    contadorPapel++;
                    actualizarContadores();
                    break;
                }
            }
        }
    }
}


void MainWindow::objectDestroyedHandler(const QString &tipoObjeto) {
    if (tipoObjeto == "jugador") {
        // Implementa lo que necesites hacer cuando el jugador sea destruido
        // Por ejemplo, detener el juego, mostrar un mensaje, etc.
    } else if (tipoObjeto == "tijeras") {
        contadorTijeras--;
    } else if (tipoObjeto == "piedra") {
        contadorPiedra--;
    } else if (tipoObjeto == "papel") {
        contadorPapel--;
    }
    actualizarContadores();
}


void MainWindow::actualizarContadores() {
    ui->lblContadorTijeras->setText(QString("Tijeras: %1").arg(contadorTijeras));
    ui->lblContadorPiedra->setText(QString("Piedras: %1").arg(contadorPiedra));
    ui->lblContadorPapel->setText(QString("Papeles: %1").arg(contadorPapel));
    ui->lblPuntajeJugador->setText(QString("Puntaje: %1").arg(puntajeJugador));
}

void MainWindow::actualizarTiempo() {
    if (modoJugador) {
        tiempoRestante--;
        ui->lblTiempo->setText(QString("Tiempo restante: %1").arg(tiempoRestante));
        if (tiempoRestante == 0) {
            timer->stop();
            timerGeneracion->stop();
            ui->lblTiempo->setText("Fin de juego");
            // Determinar y mostrar el ganador aquí
        }
    }
}

void MainWindow::manejarDestruccionObjeto(const QString &tipoObjeto) {
    if (tipoObjeto == "jugador") {
        // Implementa lo que necesites hacer cuando el jugador sea destruido
        // Por ejemplo, detener el juego, mostrar un mensaje, etc.
    } else if (tipoObjeto == "tijeras") {
        contadorTijeras--;
    } else if (tipoObjeto == "piedra") {
        contadorPiedra--;
    } else if (tipoObjeto == "papel") {
        contadorPapel--;
    }
    actualizarContadores();
}


void MainWindow::mousePressEvent(QMouseEvent *event) {
    setFocus();
    QMainWindow::mousePressEvent(event);
}
