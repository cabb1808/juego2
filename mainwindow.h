#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>
#include "personaje.h"
#include "obstaculo.h"
#include <QKeyEvent>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QImage>
#include "enemy.h"
#include <stdlib.h>
#include <time.h>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void actualizar();
    void spawn();
    void spawn2();


private:
    QImage image,image2,image3,image4;

    Ui::MainWindow *ui;
    QTimer *timer;                        // timer para los intervalos de tiempo de visualizacion
    QTimer *timer2;
    QTimer *timer3;
    QGraphicsScene *scene;                // scene que muestra los objetos animados
    float dt;                             // intervalo de tiempo de visualizacion
    int limitX;                           // longitud en X del mundo
    int limitY;                           // longitud en Y del mundo
    int level=1;
    void bordercollision(personaje *b);   //detecta colisiones con los bordes del mundo para detenerlo
    void keyPressEvent(QKeyEvent *event);
    personaje *principal=new personaje(32,150,0,0,20,30,0.08,0);              //lista con los cuerpos para mostrarlos.
    obstaculo *fire=new obstaculo(100,40);
    obstaculo *fire2=new obstaculo(100,40);
    obstaculo *fire3=new obstaculo(110,40);
    enemy *enemigo=new enemy;
    void nivel();
};
#endif // MAINWINDOW_H
