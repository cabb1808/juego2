#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>
#include "personaje.h"
#include "obstaculos.h"
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

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;                        // timer para los intervalos de tiempo de visualizacion
    QGraphicsScene *scene;                // scene que muestra los objetos animados
    float dt;                             // intervalo de tiempo de visualizacion
    int limitX;                           // longitud en X del mundo
    int limitY;                           // longitud en Y del mundo
    void bordercollision(personaje *b);   //detecta colisiones con los bordes del mundo para detenerlo
    void keyPressEvent(QKeyEvent *event);
    personaje *principal=new personaje(32,150,0,0,20,30,0.08,0);              //lista con los cuerpos para mostrarlos.

};
#endif // MAINWINDOW_H
