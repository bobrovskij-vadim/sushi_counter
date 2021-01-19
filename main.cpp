#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *window = new MainWindow;
    window->resize(430,600);
    window->show();


    //MainWindow w;
    //w.show();


    return a.exec();
}
