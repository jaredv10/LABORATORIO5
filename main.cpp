#include <QApplication>
#include <QTime>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    qsrand(QTime::currentTime().msec());

    MainWindow w;
    w.show();
    return a.exec();
}

