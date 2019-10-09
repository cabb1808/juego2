#include "mainwindow.h"
#include "menu.h"
#include <QTimer>
#include <QApplication>
#include <time.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Menu *menu=new Menu;
    menu->show();
    //MainWindow w;
    //w.show();


    return a.exec();

}
