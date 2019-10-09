#include "mainwindow.h"
#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Menu menu;
    menu.show();
    return a.exec();

}
