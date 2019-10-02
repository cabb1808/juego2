#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <time.h>
#include <QKeyEvent>
#include "obstaculos.h"
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    limitX=1000;                   //Asigna el tamaño de la interfaz
    limitY=800;


    principal->setEscala(5);
    timer=new QTimer(this);                 //crea el timer
    scene=new QGraphicsScene(this);         //crea la scene
    scene->setSceneRect(0,0,limitX,limitY); //establece el tamaño y posicion del scene

    scene->setBackgroundBrush(QBrush(QImage(":/images/fondo")));

    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();
    scene->addRect(scene->sceneRect());

    ui->graphicsView->resize(scene->width(),scene->height());
    this->resize(ui->graphicsView->width()+100, ui->graphicsView->height()+100);

    principal->setFlag(QGraphicsItem::ItemIsFocusable);
    principal->setFocus();
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    timer -> start(20);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{

        // Utilizamos la funcion Set_vel de personaje para que cada vez que presione una tecla
        //           cambie su velocidad y le de un movimiento

        if (event->key() == Qt::Key_6 ){
            principal->set_vel(30,principal->get_velY(),principal->get_posX(), principal->get_posY());
        }
        if (event->key() == Qt::Key_4 ){
            principal->set_vel(-30,principal->get_velY(),principal->get_posX(), principal->get_posY());
        }
        if (event->key() == Qt::Key_8 /*&& principal->get_posY()<=principal->get_Radio()+80*/){
            principal->set_vel(principal->get_velX(),50,principal->get_posX(), principal->get_posY());
        }
        if (event->key() == Qt::Key_Space){
            timer->start(6);
            principal->actualizar(limitY);
            scene->addItem(principal);
        }

}
void MainWindow::actualizar()
{
        principal->actualizar(limitY);//actualiza en esferagraf
        bordercollision(principal);//actualiza el choque con el borde

}

void MainWindow::bordercollision(personaje *b)//son los choques con los bordes
{
    if(b->get_posX()<b->get_Radio()){
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), b->get_Radio(), b->get_posY()) ;//con el borde izquierdo

    }
    if(b->get_posX()>limitX-b->get_Radio()){//posicion con el borde derecho.
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), limitX-b->get_Radio(), b->get_posY());
    }
    if(b->get_posY()<b->get_Radio()){//choque con el borde superior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), (b->get_posX()), b->get_Radio());
    }
    if(b->get_posY()>limitY-b->get_Radio()){//choque con el borde inferior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-b->get_Radio());
    }
    if(b->get_posX()>600-b->get_Radio() && b->get_posX()<610-b->get_Radio() && b->get_posY()<limitY-600-b->get_Radio() ){//posicion con el borde derecho.
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 600-b->get_Radio(), b->get_posY());
    }
    if(b->get_posX()>740-b->get_Radio() && b->get_posX()<750-b->get_Radio() && b->get_posY()<limitY-600-b->get_Radio() ){//posicion con el borde derecho.
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 750-b->get_Radio(), b->get_posY());
    }
    if(b->get_posY()<limitY-600-b->get_Radio() && b->get_posX()>600-b->get_Radio() && b->get_posX()<750-b->get_Radio()){//choque con el borde inferior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-600-b->get_Radio());
     }

}

