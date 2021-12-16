#include "src/headers/globals.h"
#include "src/headers/mainwindow.h"

#include <QApplication>

// Main QT project funcion
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
